#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#ifdef _MSC_VER
#include <windows.h>
#endif
#include <GL/gl.h>


#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igSliderFloat igSliderFloat_Str
#define igCheckbox igCheckbox_Str
#define igColorEdit3 igColorEdit3_Str
#define igButton igButton_Str
#endif

GLFWwindow *window;

int main(int argc, char *argv[])
{

  if (!glfwInit())
    return -1;

  // Decide GL+GLSL versions
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

#if __APPLE__
  // GL 3.2 Core + GLSL 150
  const char *glsl_version = "#version 150";
#else
  // GL 3.2 + GLSL 130
  const char *glsl_version = "#version 130";
#endif

  // just an extra window hint for resize
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(1024, 768, "Hello World!", NULL, NULL);
  if (!window) 
  {
    printf("Failed to create window! Terminating!\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // enable vsync
  glfwSwapInterval(1);

  // check opengl version sdl uses
  printf("opengl version: %s\n", (char *)glGetString(GL_VERSION));

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

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

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
    ImGui_ImplOpenGL3_NewFrame();
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
    glfwMakeContextCurrent(window);
    glViewport(0, 0, (int)ioptr->DisplaySize.x, (int)ioptr->DisplaySize.y);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
#ifdef IMGUI_HAS_DOCK
    if (ioptr->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) 
    {
      GLFWwindow *backup_current_window = glfwGetCurrentContext();
      igUpdatePlatformWindows();
      igRenderPlatformWindowsDefault(NULL, NULL);
      glfwMakeContextCurrent(backup_current_window);
    }
#endif
    glfwSwapBuffers(window);
  }

  // clean up
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(NULL);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
