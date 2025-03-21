#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

#include <cimgui.h>
#include <cimgui_impl.h>

#define CHECK(x)                                                               \
  do {                                                                         \
    void *value = (void *)x;                                                   \
    if (!value || (void *)value == NULL) {                                     \
      fprintf(stderr, "SDL Error: %s", SDL_GetError());                        \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

int main() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Failed to init video! %s", SDL_GetError());
    return 1;
  };

  SDL_Window *window = NULL;
  window = SDL_CreateWindow("Dung", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  assert(window);

  SDL_GPUDevice *device =
      SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_DXIL |
                              SDL_GPU_SHADERFORMAT_SPIRV,
                          true, NULL);
  assert(device);

  const char *device_driver = SDL_GetGPUDeviceDriver(device);
  CHECK(device_driver);

  CHECK(SDL_ClaimWindowForGPUDevice(device, window));

  // setup imgui
  igCreateContext(NULL);

  // set docking
  ImGuiIO *ioptr = igGetIO();
  ioptr->ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  // ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable
  // Gamepad Controls
#ifdef IMGUI_HAS_DOCK
  ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  ioptr->ConfigFlags |=
      ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform
                                        // Windows
#endif

  assert(ImGui_ImplSDL3_InitForSDLGPU(window));
  assert(ImGui_ImplSDLGPU3_Init(&(ImGui_ImplSDLGPU3_InitInfo){
      .ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(device, window),
      .Device = device,
      .MSAASamples = SDL_GPU_SAMPLECOUNT_1,
  }));

  // finish loading data

  bool running = true;
  SDL_Event e;
  uint64_t now = SDL_GetTicks();
  uint64_t previous = now;
  uint64_t last_frame_time = now;
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);
  bool demo_window_open = true;

  while (running) {
    const uint64_t ts = now - previous;

    while (SDL_PollEvent(&e)) {
      ImGui_ImplSDL3_ProcessEvent(&e);
      switch (e.type) {
      case SDL_EVENT_KEY_DOWN: {
        switch (e.key.scancode) {
        case SDL_SCANCODE_GRAVE: {
          demo_window_open = !demo_window_open;
        } break;

        case SDL_SCANCODE_ESCAPE: {
          running = false;
        } break;

        default:
          continue;
        }
      } break;
      case SDL_EVENT_QUIT: {
        running = false;
      } break;
      default:;
      }
    }

    previous = now;
    now = SDL_GetTicks();
    if (now - last_frame_time >= SCREEN_TICKS_PER_FRAME) {
      last_frame_time = now;

      ImGui_ImplSDLGPU3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      igNewFrame();

      if (demo_window_open) {
        igShowDemoWindow(&demo_window_open);
      }

      igRender();

      SDL_GPUCommandBuffer *cmdbuf = SDL_AcquireGPUCommandBuffer(device);
      if (cmdbuf == NULL) {
        fprintf(stderr, "ERROR: SDL_AcquireGPUCommandBuffer failed: %s\n",
                SDL_GetError());
        break;
      }

      SDL_GPUTexture *swapchain_texture;
      if (!SDL_WaitAndAcquireGPUSwapchainTexture(
              cmdbuf, window, &swapchain_texture, NULL, NULL)) {
        fprintf(stderr,
                "ERROR: SDL_WaitAndAcquireGPUSwapchainTexture failed: %s\n",
                SDL_GetError());
        break;
      }

      if (swapchain_texture == NULL) {
        fprintf(stderr, "ERROR: swapchain_texture is NULL\n");
        SDL_SubmitGPUCommandBuffer(cmdbuf);
        break;
      }

      SDL_GPUColorTargetInfo color_target_info = {0};
      color_target_info.texture = swapchain_texture;
      color_target_info.clear_color = (SDL_FColor){0, 0, 0, 1};
      color_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
      color_target_info.store_op = SDL_GPU_STOREOP_STORE;

      ImDrawData *imgui_draw_data = igGetDrawData();
      Imgui_ImplSDLGPU3_PrepareDrawData(imgui_draw_data, cmdbuf);

      SDL_GPURenderPass *render_pass =
          SDL_BeginGPURenderPass(cmdbuf, &color_target_info, 1, NULL);
      CHECK(render_pass);

      ImGui_ImplSDLGPU3_RenderDrawData(imgui_draw_data, cmdbuf, render_pass,
                                       NULL);

      SDL_EndGPURenderPass(render_pass);
      CHECK(SDL_SubmitGPUCommandBuffer(cmdbuf));
    }
  }
  return 0;
}
