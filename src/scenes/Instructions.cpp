#include "Instructions.h"

#include <raylib.h>

#include "Constants.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

namespace {
void Draw() {
  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);

  BeginDrawing();
  {
    ClearBackground(BLACK);

    DrawTexturePro(k_Background,
                   {0,
                    0,
                    static_cast<float>(k_Background.width),
                    static_cast<float>(k_Background.height)},
                   {0,
                    0,
                    static_cast<float>(g_ScreenWidth),
                    static_cast<float>(g_ScreenHeight)}, {0, 0}, 0, WHITE);

    DrawText("How To Play",
             (g_ScreenWidth - MeasureText("How To Play!", 60)) / 2, 120, 60,
             WHITE);
    DrawText(
        "The objective is to survive as long as you can agains a hord of demons.",
        (g_ScreenWidth - MeasureText(
             "The objective is to survive as long as you can agains a hord of demons.",
             20)) / 2, 200, 20, WHITE);
    DrawText(
        "For that, you have your trusty jetpack, which you control using the mouse,",
        (g_ScreenWidth - MeasureText(
             "For that, you have your trusty jetpack, which you control using the mouse",
             20)) / 2, 240, 20, WHITE);
    DrawText(
        "to aim and the right click to accelerate. You also can shut your shotgun with left-click.",
        (g_ScreenWidth - MeasureText(
             "to aim and the right click to accelerate. You also can shut your shotgun with left-click.",
             20)) / 2, 260, 20, WHITE);
    DrawText("Press any key to continue",
            (g_ScreenWidth - MeasureText("Press any key to continue", 60)) / 2,
            600, 60, WHITE);
  }
  EndDrawing();

}
}



void Instructions::Instructions() {
  while (!GetKeyPressed() && !WindowShouldClose()) {
    Draw();
  }
  if (WindowShouldClose()) {
    ChangeScene(SceneManager::Scenes::Exit);
  } else {
    SceneManager::ChangeScene();
  }
}
