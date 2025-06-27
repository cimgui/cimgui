#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_SDL3
#define CIMGUI_USE_SDLRENDERER3
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../cimgui.h"
#include "../cimgui_impl.h"

int main(int argc, char **argv)
{
  // Initialize SDL3
  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  // Create SDL3 window and renderer
  SDL_Window *window = SDL_CreateWindow(
    "SDL3 + cimgui Demo", 800, 600, SDL_WINDOW_RESIZABLE);
  if (!window)
  {
    SDL_Log(
      "Failed to create window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer)
  {
    SDL_Log(
      "Failed to create renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Setup Dear ImGui context
  ImGuiContext *context = igCreateContext(NULL);
  ImGuiIO      *io      = igGetIO_ContextPtr(context);
  io->IniFilename = NULL; // Skip saving/loading settings

  // Initialize ImGui SDL3 + SDL_Renderer backends
  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  // --- Render a single frame ---
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    ImGui_ImplSDL3_ProcessEvent(&event);
  }

  ImGui_ImplSDL3_NewFrame();
  ImGui_ImplSDLRenderer3_NewFrame();
  igNewFrame();

  // Show the built-in demo window
  igShowDemoWindow(NULL);

  igRender();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  ImGui_ImplSDLRenderer3_RenderDrawData(
    igGetDrawData(), renderer);
  SDL_RenderPresent(renderer);

  SDL_Delay(1000); // Optional: let the user see the frame

  // --- Cleanup ---
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  igDestroyContext(context);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
