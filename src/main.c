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
  #ifdef __linux__
  char *app_dir = getenv(ENV_APP_DIR);
  if (app_dir != NULL)
    return app_dir;
  #endif

  return getenv(ENV_ROOT_DIR);
}

// Path limits
#ifdef __linux__
#include <linux/limits.h>
char fixed_path[PATH_MAX];
#else
char fixed_path[255];
#endif

char *from_root_dir(char *path)
{
  char *root_dir = get_root_dir();
  if (root_dir == NULL) {
    return path;
  }
  sprintf(fixed_path, "%s/%s", root_dir, path);
  return fixed_path;
}


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