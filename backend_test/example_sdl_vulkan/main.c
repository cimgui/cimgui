#include <stdio.h>
#include <assert.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#ifdef _MSC_VER
#include <windows.h>
#endif

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igSliderFloat igSliderFloat_Str
#define igCheckbox igCheckbox_Str
#define igColorEdit3 igColorEdit3_Str
#define igButton igButton_Str
#endif

#define IM_UNUSED(_VAR)  ((void)(_VAR))
#define IM_ASSERT(_EXPR) assert(_EXPR)
#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))

static VkAllocationCallbacks*   g_Allocator = NULL;
static VkInstance               g_Instance = VK_NULL_HANDLE;
static VkPhysicalDevice         g_PhysicalDevice = VK_NULL_HANDLE;
static VkDevice                 g_Device = VK_NULL_HANDLE;
static uint32_t                 g_QueueFamily = (uint32_t)-1;
static VkQueue                  g_Queue = VK_NULL_HANDLE;
static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
static VkPipelineCache          g_PipelineCache = VK_NULL_HANDLE;
static VkDescriptorPool         g_DescriptorPool = VK_NULL_HANDLE;

static ImGui_ImplVulkanH_Window g_MainWindowData;
static uint32_t                 g_MinImageCount = 2;
static bool                     g_SwapChainRebuild = false;

static void check_vk_result(VkResult err)
{
    if (err == 0)
        return;
    fprintf(stderr, "[vulkan] Error: VkResult = %d\n", err);
    if (err < 0)
        abort();
}

#ifdef IMGUI_VULKAN_DEBUG_REPORT
static VKAPI_ATTR VkBool32 VKAPI_CALL debug_report(VkDebugReportFlagsEXT flags,
  VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location,
  int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData)
{
    (void)flags; (void)object; (void)location; (void)messageCode;
    (void)pUserData; (void)pLayerPrefix; // Unused arguments
    fprintf(stderr, "[vulkan] Debug report from ObjectType: %i\nMessage: %s\n\n",
      objectType, pMessage);
    return VK_FALSE;
}
#endif // IMGUI_VULKAN_DEBUG_REPORT

static void SetupVulkan(const char** extensions, uint32_t extensions_count)
{
  VkResult err;

  // Create Vulkan Instance
  VkInstanceCreateInfo inst_create_info = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .enabledExtensionCount = extensions_count,
    .ppEnabledExtensionNames = extensions,
  };
#ifdef IMGUI_VULKAN_DEBUG_REPORT
  // Enabling validation layers
  const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
  inst_create_info.enabledLayerCount = 1;
  inst_create_info.ppEnabledLayerNames = layers;

  // Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
  const char** extensions_ext = (const char**)malloc(
      sizeof(const char*) * (extensions_count + 1));
  memcpy(extensions_ext, extensions, extensions_count * sizeof(const char*));
  extensions_ext[extensions_count] = "VK_EXT_debug_report";
  inst_create_info.enabledExtensionCount = extensions_count + 1;
  inst_create_info.ppEnabledExtensionNames = extensions_ext;

  // Create Vulkan Instance
  err = vkCreateInstance(&inst_create_info, g_Allocator, &g_Instance);
  check_vk_result(err);
  free(extensions_ext);

  // Get the function pointer (required for any extensions)
  PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT =
    (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance,
      "vkCreateDebugReportCallbackEXT");
  IM_ASSERT(vkCreateDebugReportCallbackEXT != NULL);

  // Setup the debug report callback
  VkDebugReportCallbackCreateInfoEXT debug_report_ci = {
    .sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT,
    .flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
             VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT,
    .pfnCallback = debug_report,
    .pUserData = NULL,
  };
  err = vkCreateDebugReportCallbackEXT(g_Instance, &debug_report_ci, g_Allocator,
    &g_DebugReport);
  check_vk_result(err);
#else
  // Create Vulkan Instance without any debug feature
  err = vkCreateInstance(&inst_create_info, g_Allocator, &g_Instance);
  check_vk_result(err);
  IM_UNUSED(g_DebugReport);
#endif

  // Select GPU
  uint32_t gpu_count;
  err = vkEnumeratePhysicalDevices(g_Instance, &gpu_count, NULL);
  check_vk_result(err);
  IM_ASSERT(gpu_count > 0);

  VkPhysicalDevice* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
  err = vkEnumeratePhysicalDevices(g_Instance, &gpu_count, gpus);
  check_vk_result(err);

  // If a number >1 of GPUs got reported, find discrete GPU if present, or use first one available. This covers
  // most common cases (multi-gpu/integrated+dedicated graphics). Handling more complicated setups (multiple
  // dedicated GPUs) is out of scope of this sample.
  int use_gpu = 0;
  for (int i = 0; i < (int)gpu_count; i++)
  {
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(gpus[i], &properties);
    if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        use_gpu = i;
        break;
    }
  }

  g_PhysicalDevice = gpus[use_gpu];
  free(gpus);

  // Select graphics queue family
  uint32_t count;
  vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, NULL);
  VkQueueFamilyProperties* queues = (VkQueueFamilyProperties*)malloc(
      sizeof(VkQueueFamilyProperties) * count);
  vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, queues);
  for (uint32_t i = 0; i < count; i++)
    if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      g_QueueFamily = i;
      break;
    }
  free(queues);
  IM_ASSERT(g_QueueFamily != (uint32_t)-1);

  // Create Logical Device (with 1 queue)
  int device_extension_count = 1;
  const char* device_extensions[] = { "VK_KHR_swapchain" };
  const float queue_priority[] = { 1.0f };
  VkDeviceQueueCreateInfo queue_info[1] = {
    [0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    [0].queueFamilyIndex = g_QueueFamily,
    [0].queueCount = 1,
    [0].pQueuePriorities = queue_priority,
  };
  VkDeviceCreateInfo create_info = {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]),
    .pQueueCreateInfos = queue_info,
    .enabledExtensionCount = device_extension_count,
    .ppEnabledExtensionNames = device_extensions,
  };
  err = vkCreateDevice(g_PhysicalDevice, &create_info, g_Allocator, &g_Device);
  check_vk_result(err);
  vkGetDeviceQueue(g_Device, g_QueueFamily, 0, &g_Queue);

  // Create Descriptor Pool
  VkDescriptorPoolSize pool_sizes[] = {
      { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
      { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
      { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
      { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
      { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
  };
  VkDescriptorPoolCreateInfo pool_info = {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
    .maxSets = 1000 * IM_ARRAYSIZE(pool_sizes),
    .poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes),
    .pPoolSizes = pool_sizes,
  };
  err = vkCreateDescriptorPool(g_Device, &pool_info, g_Allocator, &g_DescriptorPool);
  check_vk_result(err);
}

// All the ImGui_ImplVulkanH_XXX structures/functions are optional helpers used by the demo.
// Your real engine/app may not use them.
static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface,
                              int width, int height)
{
    wd->Surface = surface;

    // Check for WSI support
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(g_PhysicalDevice, g_QueueFamily, wd->Surface, &res);
    if (res != VK_TRUE)
    {
        fprintf(stderr, "Error no WSI support on physical device 0\n");
        exit(-1);
    }

    // Select Surface Format
    const VkFormat requestSurfaceImageFormat[] = {
        VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
        VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM
    };
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(
      g_PhysicalDevice, wd->Surface, requestSurfaceImageFormat,
      (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    // Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
    VkPresentModeKHR present_modes[] = {
      VK_PRESENT_MODE_MAILBOX_KHR,VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR
    };
#else
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(
      g_PhysicalDevice, wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));

    // Create SwapChain, RenderPass, Framebuffer, etc.
    IM_ASSERT(g_MinImageCount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(
      g_Instance, g_PhysicalDevice, g_Device, wd, g_QueueFamily, g_Allocator,
      width, height, g_MinImageCount);
}

static void CleanupVulkan()
{
  vkDestroyDescriptorPool(g_Device, g_DescriptorPool, g_Allocator);

#ifdef IMGUI_VULKAN_DEBUG_REPORT
  // Remove the debug report callback
  PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT =
    (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkDestroyDebugReportCallbackEXT");
  vkDestroyDebugReportCallbackEXT(g_Instance, g_DebugReport, g_Allocator);
#endif // IMGUI_VULKAN_DEBUG_REPORT

  vkDestroyDevice(g_Device, g_Allocator);
  vkDestroyInstance(g_Instance, g_Allocator);
}

static void CleanupVulkanWindow()
{
  ImGui_ImplVulkanH_DestroyWindow(g_Instance, g_Device, &g_MainWindowData, g_Allocator);
}

static void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data)
{
  VkResult err;

  VkSemaphore image_acquired_semaphore  = wd->FrameSemaphores[wd->SemaphoreIndex].ImageAcquiredSemaphore;
  VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
  err = vkAcquireNextImageKHR(g_Device, wd->Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &wd->FrameIndex);
  if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
  {
    g_SwapChainRebuild = true;
    return;
  }
  check_vk_result(err);

  ImGui_ImplVulkanH_Frame* fd = &wd->Frames[wd->FrameIndex];
  err = vkWaitForFences(g_Device, 1, &fd->Fence, VK_TRUE, UINT64_MAX);    // wait indefinitely instead of periodically checking
  check_vk_result(err);

  err = vkResetFences(g_Device, 1, &fd->Fence);
  check_vk_result(err);

  err = vkResetCommandPool(g_Device, fd->CommandPool, 0);
  check_vk_result(err);
  VkCommandBufferBeginInfo info = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };
  err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
  check_vk_result(err);
  VkRenderPassBeginInfo rp_info = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
    .renderPass = wd->RenderPass,
    .framebuffer = fd->Framebuffer,
    .renderArea.extent.width = wd->Width,
    .renderArea.extent.height = wd->Height,
    .clearValueCount = 1,
    .pClearValues = &wd->ClearValue,
  };
  vkCmdBeginRenderPass(fd->CommandBuffer, &rp_info, VK_SUBPASS_CONTENTS_INLINE);

  // Record dear imgui primitives into command buffer
  ImGui_ImplVulkan_RenderDrawData(draw_data, fd->CommandBuffer, VK_NULL_HANDLE);

  // Submit command buffer
  vkCmdEndRenderPass(fd->CommandBuffer);
  VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  VkSubmitInfo sub_info = {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .waitSemaphoreCount = 1,
    .pWaitSemaphores = &image_acquired_semaphore,
    .pWaitDstStageMask = &wait_stage,
    .commandBufferCount = 1,
    .pCommandBuffers = &fd->CommandBuffer,
    .signalSemaphoreCount = 1,
    .pSignalSemaphores = &render_complete_semaphore,
  };

  err = vkEndCommandBuffer(fd->CommandBuffer);
  check_vk_result(err);
  err = vkQueueSubmit(g_Queue, 1, &sub_info, fd->Fence);
  check_vk_result(err);
}

static void FramePresent(ImGui_ImplVulkanH_Window* wd)
{
  if (g_SwapChainRebuild) return;
  VkSemaphore render_complete_semaphore = wd->FrameSemaphores[wd->SemaphoreIndex].RenderCompleteSemaphore;
  VkPresentInfoKHR info = {
    .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
    .waitSemaphoreCount = 1,
    .pWaitSemaphores = &render_complete_semaphore,
    .swapchainCount = 1,
    .pSwapchains = &wd->Swapchain,
    .pImageIndices = &wd->FrameIndex,
  };
  VkResult err = vkQueuePresentKHR(g_Queue, &info);
  if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
  {
    g_SwapChainRebuild = true;
    return;
  }
  check_vk_result(err);
  wd->SemaphoreIndex = (wd->SemaphoreIndex + 1) % wd->ImageCount; // Now we can use the next set of semaphores
}

int main(int argc, char* argv[])
{

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_Log("failed to init: %s", SDL_GetError());
    return -1;
  }

  /// Setup window
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN |
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window = SDL_CreateWindow("cImGui SDL2+Vulkan example",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  if (window == NULL) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return -1;
  }

  // Setup Vulkan
  uint32_t extensions_count = 0;
  SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, NULL);
  const char** extensions = malloc(extensions_count * sizeof(const char*));
  SDL_Vulkan_GetInstanceExtensions(window, &extensions_count, extensions);
  SetupVulkan(extensions, extensions_count);
  free(extensions);

  // Create Window Surface
  VkSurfaceKHR surface;
  VkResult err;
  if (SDL_Vulkan_CreateSurface(window, g_Instance, &surface) == 0)
  {
      printf("Failed to create Vulkan surface.\n");
      return 1;
  }

  // Create Framebuffers
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  ImGui_ImplVulkanH_Window* wd = &g_MainWindowData;
  SetupVulkanWindow(wd, surface, w, h);

  // setup imgui
  igCreateContext(NULL);

  //set docking
  ImGuiIO* ioptr = igGetIO();
  ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
  //ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForVulkan(window);
  ImGui_ImplVulkan_InitInfo init_info = {
    .Instance = g_Instance,
    .PhysicalDevice = g_PhysicalDevice,
    .Device = g_Device,
    .QueueFamily = g_QueueFamily,
    .Queue = g_Queue,
    .PipelineCache = g_PipelineCache,
    .DescriptorPool = g_DescriptorPool,
    .Subpass = 0,
    .MinImageCount = g_MinImageCount,
    .ImageCount = wd->ImageCount,
    .MSAASamples = VK_SAMPLE_COUNT_1_BIT,
    .Allocator = g_Allocator,
    .CheckVkResultFn = check_vk_result
  };
  ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);

  igStyleColorsDark(NULL);

  // Upload Fonts
  // Use any command queue
  VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
  VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

  err = vkResetCommandPool(g_Device, command_pool, 0);
  check_vk_result(err);
  VkCommandBufferBeginInfo begin_info = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };
  err = vkBeginCommandBuffer(command_buffer, &begin_info);
  check_vk_result(err);

  ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

  VkSubmitInfo end_info = {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .commandBufferCount = 1,
    .pCommandBuffers = &command_buffer,
  };
  err = vkEndCommandBuffer(command_buffer);
  check_vk_result(err);
  err = vkQueueSubmit(g_Queue, 1, &end_info, VK_NULL_HANDLE);
  check_vk_result(err);

  err = vkDeviceWaitIdle(g_Device);
  check_vk_result(err);
  ImGui_ImplVulkan_DestroyFontUploadObjects();

  bool showDemoWindow = true;
  bool showAnotherWindow = false;
  ImVec4 clearColor;
  clearColor.x = 0.45f;
  clearColor.y = 0.55f;
  clearColor.z = 0.60f;
  clearColor.w = 1.00f;

  bool quit = false;
  while (!quit)
  {
    SDL_Event e;

    // we need to call SDL_PollEvent to let window rendered, otherwise
    // no window will be shown
    while (SDL_PollEvent(&e) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&e);
      if (e.type == SDL_QUIT)
        quit = true;
      if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE &&
          e.window.windowID == SDL_GetWindowID(window))
        quit = true;
    }

    // Resize swap chain
    if (g_SwapChainRebuild)
    {
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        if (width > 0 && height > 0)
        {
            ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(
              g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData,
              g_QueueFamily, g_Allocator, width, height, g_MinImageCount);
            g_MainWindowData.FrameIndex = 0;
            g_SwapChainRebuild = false;
        }
    }

    // start imgui frame
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    igNewFrame();

    if (showDemoWindow)
      igShowDemoWindow(&showDemoWindow);

    // show a simple window that we created ourselves.
    {
      static float f = 0.0f;
      static int counter = 0;

      igBegin("Hello, world!", NULL, 0);
      igText("This is some useful text");
      igCheckbox("Demo window", &showDemoWindow);
      igCheckbox("Another window", &showAnotherWindow);

      igSliderFloat("Float", &f, 0.0f, 1.0f, "%.3f", 0);
      igColorEdit3("clear color", (float*)&clearColor, 0);

      ImVec2 buttonSize;
      buttonSize.x = 0;
      buttonSize.y = 0;
      if (igButton("Button", buttonSize))
        counter++;
      igSameLine(0.0f, -1.0f);
      igText("counter = %d", counter);

      igText("Application average %.3f ms/frame (%.1f FPS)",
             1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
      igEnd();
    }

    if (showAnotherWindow)
    {
      igBegin("imgui Another Window", &showAnotherWindow, 0);
      igText("Hello from imgui");
      ImVec2 buttonSize;
      buttonSize.x = 0; buttonSize.y = 0;
      if (igButton("Close me", buttonSize))
      {
        showAnotherWindow = false;
      }
      igEnd();
    }

    // render
    igRender();
    ImDrawData* draw_data = igGetDrawData();
    const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
    if (!is_minimized)
    {
        wd->ClearValue.color.float32[0] = clearColor.x * clearColor.w;
        wd->ClearValue.color.float32[1] = clearColor.y * clearColor.w;
        wd->ClearValue.color.float32[2] = clearColor.z * clearColor.w;
        wd->ClearValue.color.float32[3] = clearColor.w;
        FrameRender(wd, draw_data);
        FramePresent(wd);
    }
  }

  // Cleanup
  err = vkDeviceWaitIdle(g_Device);
  check_vk_result(err);
  ImGui_ImplVulkan_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  igDestroyContext(NULL);

  CleanupVulkanWindow();
  CleanupVulkan();

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}