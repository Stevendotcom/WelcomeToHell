#include "Credits.h"

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
    DrawText("Thanks For playing!",
             (g_ScreenWidth - MeasureText("Thanks For playing!", 60)) / 2, 120,
             60, WHITE);
    DrawText("Background and character by myself",
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
    DrawText("Press any key to continue",
             (g_ScreenWidth - MeasureText("Press any key to continue", 60)) / 2,
             600, 60, WHITE);
  }
  EndDrawing();

}
}



void Credits::Credits() {
  while (!GetKeyPressed() && !WindowShouldClose()) {
    Draw();
  }
  if (WindowShouldClose()) {
    ChangeScene(SceneManager::Scenes::Exit);
  } else {
    SceneManager::ChangeScene();
  }
}
