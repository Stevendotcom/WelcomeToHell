#include "Instructions.h"

#include "raylib.h"

#include "Constants.h"
#include "engine/Math.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

namespace {
constexpr Rectangle k_Dest = {30, 700, 250.0F, 50.0F};

bool IsHover = false;



bool Input() {
  const Vector2 MousePos = GetMousePosition();
  if (Math::IsInRect(k_Dest, MousePos)) {
    IsHover = true;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      return true;
    }
  }
  return false;
}



void Draw() {
  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);
  const Texture2D& k_Btn = GetTexture(ResManager::Resources::Btn);
  const Texture2D& k_BtnPressed = GetTexture(ResManager::Resources::BtnPressed);
  constexpr Rectangle k_Source = {0, 0, 58.0F, 25.0F};

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

    DrawTexturePro(IsHover ? k_BtnPressed : k_Btn, k_Source, k_Dest, {0, 0}, 0,
                   WHITE);

    DrawText("Return",
             static_cast<int>(k_Dest.x + (
                                k_Dest.width - static_cast<float>(
                                  MeasureText("Return", 20))) / 2.0F),
             static_cast<int>(k_Dest.y + (k_Dest.height - 20) / 2), 20, WHITE);
  }
  EndDrawing();

}
}



void Instructions::Instructions() {
  while (!Input() && !WindowShouldClose()) {
    Draw();
  }
  if (WindowShouldClose()) {
    ChangeScene(SceneManager::Scenes::Exit);
  } else {
    SceneManager::ChangeScene();
  }
}
