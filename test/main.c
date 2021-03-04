#include <stdio.h>
#include <assert.h>
#include "../cimgui.h"

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Strv
#define igSliderFloat igSliderFloat_Strv
#define igCheckbox igCheckbox_Strv
#define igColorEdit3 igColorEdit3_Strv
#define igButton igButton_Strv
#endif

int main(void)
{
  assert(igDebugCheckVersionAndDataLayout(igGetVersion(), sizeof(ImGuiIO), sizeof(ImGuiStyle),
                                          sizeof(ImVec2), sizeof(ImVec4), sizeof(ImDrawVert),
                                          sizeof(ImDrawIdx)));
  printf("CreateContext() - v%s\n", igGetVersion());
  igCreateContext(NULL);
  ImGuiIO *io = igGetIO();

  unsigned char *text_pixels = NULL;
  int text_w, text_h;
  ImFontAtlas_GetTexDataAsRGBA32(io->Fonts, &text_pixels, &text_w, &text_h, NULL);

  for (int n = 0; n < 20; n++) {
    printf("NewFrame() %d\n", n);

    ImVec2 display_size;
    display_size.x = 1920;
    display_size.y = 1080;
    io->DisplaySize = display_size;
    io->DeltaTime = 1.0f / 60.0f;
    igNewFrame();
    
    igBegin("mainwindow",NULL,ImGuiWindowFlags_NoTitleBar);
    static float f = 0.0f;
    igText("Hello World!");
    igSliderFloat("float", &f, 0.0f, 1.0f, "%.3f", 0);
    igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    igEnd();
    igShowDemoWindow(NULL);

    igRender();
  }
  printf("%llu\n",ImGuiWindowFlags_NoTitleBar);
  printf("size: %d\n",sizeof(ImGuiWindowFlags_NoTitleBar));
  printf("DestroyContext()\n");
  igDestroyContext(NULL);

  return 0;
}
