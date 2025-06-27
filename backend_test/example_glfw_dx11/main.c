//#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS is done in cmake
#include "cimgui.h"
#include "cimgui_impl.h"
#define D3D11_NO_HELPERS
#define CINTERFACE
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include <d3d11.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif

#pragma comment(lib, "dxguid.lib")

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igSliderFloat igSliderFloat_Str
#define igCheckbox igCheckbox_Str
#define igColorEdit3 igColorEdit3_Str
#define igButton igButton_Str
#endif

#define igGetIO igGetIO_Nil

GLFWwindow *window;

// Data
static ID3D11Device*            g_pd3dDevice = NULL;
static ID3D11DeviceContext*     g_pd3dDeviceContext = NULL;
static IDXGISwapChain*          g_pSwapChain = NULL;
static ID3D11RenderTargetView*  g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();

void window_size_callback(GLFWwindow* window, int width, int height)
{
	CleanupRenderTarget();
    IDXGISwapChain_ResizeBuffers(g_pSwapChain, 0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}

int main(int argc, char *argv[])
{

  if (!glfwInit())
    return -1;

  // Decide GL+GLSL versions
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);



  // just an extra window hint for resize
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(1024, 768, "Hello World!", NULL, NULL);
  if (!window) 
  {
    printf("Failed to create window! Terminating!\n");
    glfwTerminate();
    return -1;
  }
  
  //
  HWND hwnd = glfwGetWin32Window(window);
  if (hwnd == NULL)
  {
	  printf("Failed to get win32 window! Terminating!\n");
	  glfwTerminate();
		return -1;
  }
	 // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        return 1;
    }
	
	glfwSetWindowSizeCallback(window, window_size_callback);

  // setup imgui
  igCreateContext(NULL);

  // set docking
  ImGuiIO *ioptr = igGetIO();
  ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
  //ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
#ifdef IMGUI_HAS_DOCK
  ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable Docking
  ioptr->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;     // Enable Multi-Viewport / Platform Windows
#endif

  ImGui_ImplGlfw_InitForOther(window, true);
  ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

  igStyleColorsDark(NULL);
  // ImFontAtlas_AddFontDefault(io.Fonts, NULL);

  bool showDemoWindow = true;
  bool showAnotherWindow = false;
  ImVec4 clearColor;
  clearColor.x = 0.45f;
  clearColor.y = 0.55f;
  clearColor.z = 0.60f;
  clearColor.w = 1.00f;
	
  // main event loop
  bool quit = false;
  while (!glfwWindowShouldClose(window))
  {

    glfwPollEvents();

    // start imgui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplGlfw_NewFrame();
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
      igColorEdit3("clear color", (float *)&clearColor, 0);

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
      buttonSize.x = 0;
      buttonSize.y = 0;
      if (igButton("Close me", buttonSize)) {
        showAnotherWindow = false;
      }
      igEnd();
    }

    // render
    igRender();
	const float clear_color_with_alpha[4] = { clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w };
        ID3D11DeviceContext_OMSetRenderTargets(g_pd3dDeviceContext, 1, &g_mainRenderTargetView, NULL);
        ID3D11DeviceContext_ClearRenderTargetView(g_pd3dDeviceContext, g_mainRenderTargetView, clear_color_with_alpha);
	ImGui_ImplDX11_RenderDrawData(igGetDrawData());
#ifdef IMGUI_HAS_DOCK
    if (ioptr->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
    {
      igUpdatePlatformWindows();
      igRenderPlatformWindowsDefault(NULL, NULL);
    }
#endif
    IDXGISwapChain_Present(g_pSwapChain,1, 0); // Present with vsync
    //g_pSwapChain->Present(0, 0); // Present without vsync
  }

  // clean up
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(NULL);
	
CleanupDeviceD3D();
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

// Helper functions to use DirectX11
bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { IDXGISwapChain_Release(g_pSwapChain); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { ID3D11DeviceContext_Release(g_pd3dDeviceContext); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { ID3D11Device_Release(g_pd3dDevice); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Resource* pBackBuffer;
    IDXGISwapChain_GetBuffer(g_pSwapChain, 0, &IID_ID3D11Texture2D, (void**)&pBackBuffer);
    ID3D11Device_CreateRenderTargetView(g_pd3dDevice, pBackBuffer, NULL, &g_mainRenderTargetView);
    ID3D11Texture2D_Release(pBackBuffer);
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { ID3D11RenderTargetView_Release(g_mainRenderTargetView); g_mainRenderTargetView = NULL; }
}

