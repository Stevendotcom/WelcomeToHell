#include "Credits.h"

#include <raylib.h>

#include "Constants.h"
#include "engine/Math.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

namespace {

constexpr Rectangle k_Dest = {30, 700, 250.0F, 50.0F};

bool IsHover = false;

bool Input() {
  const Vector2 MousePos = GetMousePosition();
  if (Math::IsInRect(k_Dest, MousePos) ) {
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
    DrawText("Thanks For playing!",
             (g_ScreenWidth - MeasureText("Thanks For playing!", 60)) / 2, 120,
             60, WHITE);
    DrawText("Background, character and by Nicolas Gallardo",
             (g_ScreenWidth - MeasureText("Background and character by myself",
                                          20)) / 2, 200, 20, WHITE);
    DrawText(
        "2D Pixel Art Cacodaemon Sprites, Elthen, https://elthen.itch.io/2d-pixel-art-cacodaemon-sprites",
        (g_ScreenWidth - MeasureText(
             "2D Pixel Art Cacodaemon Sprites, Elthen, https://elthen.itch.io/2d-pixel-art-cacodaemon-sprites",
             20)) / 2, 240, 20, WHITE);
    DrawText(
        "Purgatory Extreme Metal Music Pack, David KBD, http://tiny.cc/k2oszz",
        (g_ScreenWidth - MeasureText(
             "Purgatory Extreme Metal Music Pack, David KBD, http://tiny.cc/k2oszz",
             20)) / 2, 280, 20, WHITE);
    DrawText(
        "Shapeforms audio free sfx, ShapeForms, https://shapeforms.itch.io/shapeforms-audio-free-sfx",
        (g_ScreenWidth - MeasureText(
             "Shapeforms audio free sfx, ShapeForms, https://shapeforms.itch.io/shapeforms-audio-free-sfx",
             20)) / 2, 320, 20, WHITE);
    DrawText(
        "DropShip Idle, Pixabay, https://pixabay.com/sound-effects/dropship-idle-hum-84742/",
        (g_ScreenWidth - MeasureText(
             "DropShip Idle, Pixabay, https://pixabay.com/sound-effects/dropship-idle-hum-84742/",
             20)) / 2, 360, 20, WHITE);
    DrawText(
        "Snake's Authentic Gun Sounds, SnakeF8, https://f8studios.itch.io/snakes-authentic-gun-sounds",
        (g_ScreenWidth - MeasureText(
             "Snake's Authentic Gun Sounds, SnakeF8, https://f8studios.itch.io/snakes-authentic-gun-sounds",
             20)) / 2, 400, 20, WHITE);

    DrawTexturePro((IsHover ? k_BtnPressed : k_Btn),
                  k_Source, k_Dest, {0, 0}, 0, WHITE);

    DrawText("Return",
             static_cast<int>(k_Dest.x + (
                                k_Dest.width - static_cast<float>(
                                  MeasureText("Return", 20)))
                              / 2.0F),
             static_cast<int>(k_Dest.y + (k_Dest.height - 20) /
                              2), 20, WHITE);

  }
  EndDrawing();

}
}



void Credits::Credits() {
  while (!Input() && !WindowShouldClose()) {
    Draw();
  }
  if (WindowShouldClose()) {
    ChangeScene(SceneManager::Scenes::Exit);
  } else {
    SceneManager::ChangeScene();
  }
}
