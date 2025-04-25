#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "../lib/raygui/src/raygui.h"
// #include "raymath.h"

// ENV CONFIG
#define ENV_APP_DIR     "APPDIR"      // Used by Linux AppImages
#define ENV_ROOT_DIR    "ROOT_DIR"

char *get_root_dir()
{
  // Override ROOT_DIR when running as an AppImage
  char *app_dir = getenv(ENV_APP_DIR);
  if (app_dir != NULL)
    return app_dir;

  return getenv(ENV_ROOT_DIR);
}

#ifdef __linux__
#include <linux/limits.h>
char fixed_path[PATH_MAX];
char *from_root_dir(char *path)
{
  sprintf(fixed_path, "%s/%s", get_root_dir(), path);
  return fixed_path;
}
#else
char fixed_path[255];
char *from_root(char *path)
{
  char *ROOT_DIR = getenv("ROOT_DIR");  
  return path;
}
#endif


int main() {
  // Window config
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "raylib basic window");

  // GUI config
  bool showMessageBox = false;
  float font_size = GuiGetStyle(DEFAULT, TEXT_SIZE);
  GuiLoadStyle(from_root_dir("gui/style_genesis.rgs"));  

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("It works! %f", font_size), 20, 200, 20, BLACK);
    
    // GUI
    if (GuiSliderBar((Rectangle){ 20, 20, 240, 30 }, "Font size", "Max", &font_size, 5, 50))
      GuiSetStyle(DEFAULT, TEXT_SIZE, font_size);

    if (GuiButton((Rectangle){ 20, 45, 240, 30 }, "Show Message"))
      showMessageBox = true;

    if (showMessageBox)
    {
      int result = GuiMessageBox((Rectangle){ 20, 110, 500, 100 },
        "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

      if (result >= 0) showMessageBox = false;
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}