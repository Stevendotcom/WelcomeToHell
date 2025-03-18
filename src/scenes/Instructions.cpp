#include "Instructions.h"

#include "raylib.h"

#include "Constants.h"
#include "engine/Math.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

namespace {

using namespace ResManager;

constexpr Rectangle k_Dest = {30,
                              700,
                              250.0F,
                              50.0F};

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
  const Texture2D k_Background = GetTexture(Resources::Background);
  const Texture2D k_Btn = GetTexture(Resources::Btn);
  const Texture2D k_BtnPressed = GetTexture(Resources::BtnPressed);
  const Texture2D k_Demon = GetTexture(Resources::DemonSpriteMove);
  const Texture2D k_Beholder = GetTexture(Resources::Beholder);
  const Texture2D k_Hearts = GetTexture(Resources::OneUp);
  const Texture2D k_Diamonds = GetTexture(Resources::Diamond);
  const Texture2D k_Batteries = GetTexture(Resources::Batteries);

  constexpr Rectangle k_Source = {0,
                                  0,
                                  58.0F,
                                  25.0F};

  constexpr Vector2 k_Alignment = {30,
                                   300};
  constexpr Vector2 k_Sizes = {128,
                               128};

  BeginDrawing();
  {
    ClearBackground(BLACK);

    DrawTexturePro(k_Background, {0,
                                  0,
                                  static_cast<float>(k_Background.width),
                                  static_cast<float>(k_Background.height)}, {0,
                     0,
                     static_cast<float>(g_ScreenWidth),
                     static_cast<float>(g_ScreenHeight)}, {0,
                     0}, 0, WHITE);

    DrawText("How To Play",
             (g_ScreenWidth - MeasureText("How To Play!", 60)) / 2, 120, 60,
             WHITE);
    DrawText(
        "The objective is to survive as long as you can against a horde of demons.",
        (g_ScreenWidth - MeasureText(
             "The objective is to survive as long as you can against a horde of demons.",
             20)) / 2, 200, 20, WHITE);
    DrawText(
        "For that, you have your trusty jetpack, which you control using the mouse,",
        (g_ScreenWidth - MeasureText(
             "For that, you have your trusty jetpack, which you control using the mouse",
             20)) / 2, 240, 20, WHITE);
    DrawText(
        "to aim and the right click to accelerate. You also can shoot your shotgun with left-click.",
        (g_ScreenWidth - MeasureText(
             "to aim and the right click to accelerate. You also can shoot your shotgun with left-click.",
             20)) / 2, 260, 20, WHITE);

    DrawTexturePro(k_Demon, {0,
                             0,
                             k_Demon.width / 6.0f,
                             k_Demon.height / 2.0f}, {k_Alignment.x,
                     k_Alignment.y,
                     k_Sizes.x,
                     k_Sizes.y}, {0,
                                  0}, 0, WHITE);
    DrawText(
        "This is a demon. They move in random\n directions, and if you shoot them\n they subdivide in smaller demons",
        static_cast<int>(k_Alignment.x + k_Sizes.x),
        static_cast<int>(k_Alignment.y + 46), 20, WHITE);

    DrawTexturePro(k_Beholder, {0,
                                0,
                                k_Beholder.width / 6.0f,
                                k_Beholder.height / 6.0f}, {k_Alignment.x,
                     k_Alignment.y + 82,
                     k_Sizes.x,
                     k_Sizes.y}, {0,
                                  0}, 0, WHITE);
    DrawText(
        "This is a beholder. They move in\n straight lines from de edges and you\n can't kill them.",
        static_cast<int>(k_Alignment.x + k_Sizes.x),
        static_cast<int>(k_Alignment.y + 148), 20, WHITE);

    DrawTexturePro(k_Hearts, {0,
                              0,
                              k_Hearts.width / 6.0f,
                              static_cast<float>(k_Hearts.height)}, {
                       k_Alignment.x + 16,
                       k_Alignment.y + 216,
                       k_Sizes.x - 40,
                       k_Sizes.y - 40}, {0,
                                         0}, 0, WHITE);
    DrawText(
    "This is a Heart Container. If you \ncollect them they five you an extra \nheart, to a maximum of 3 hearts.",
    static_cast<int>(k_Alignment.x + k_Sizes.x),
    static_cast<int>(k_Alignment.y + 226), 20, WHITE);


    DrawTexturePro(k_Diamonds, {0,
                                0,
                                k_Diamonds.width / 6.0f,
                                static_cast<float>(k_Diamonds.height)}, {
                       k_Alignment.x + g_ScreenWidth / 2.0f,
                       k_Alignment.y + 80,
                       k_Sizes.x - 40,
                       k_Sizes.y - 40}, {0,
                                         0}, 0, WHITE);
    DrawText(
   "This is a Diamond Container. \nThey gave you extra \npoints!",
   static_cast<int>(k_Alignment.x + k_Sizes.x + g_ScreenWidth / 2.0f),
   static_cast<int>(k_Alignment.y + 100), 20, WHITE);

    DrawTexturePro(k_Batteries, {0,
                                 0,
                                 static_cast<float>(k_Batteries.width),
                                 static_cast<float>(k_Batteries.height)}, {
                       k_Alignment.x + g_ScreenWidth / 2.0f,
                       k_Alignment.y + 192,
                       k_Sizes.x - 40,
                       k_Sizes.y - 40}, {0,
                                         0}, 0, WHITE);
    DrawText(
   "This is a Battery Boost. \nThey gave you extra \nspeed for a limited time",
   static_cast<int>(k_Alignment.x + k_Sizes.x + g_ScreenWidth / 2.0f),
   static_cast<int>(k_Alignment.y + 200), 20, WHITE);

    DrawTexturePro(IsHover ? k_BtnPressed : k_Btn, k_Source, k_Dest, {0,
                     0}, 0, WHITE);

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
