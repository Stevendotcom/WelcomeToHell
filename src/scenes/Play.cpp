#include "Play.h"

#include "Constants.h"
#include "raylib.h"
#include "engine/ResManager.h"

namespace {

void Input() {
}



void Update() {
}



void Draw() {
  Texture2D& Background = GetTexture(ResManager::Resources::Background);

  BeginDrawing();
  {
    DrawTexturePro(Background,
                   {0,
                    0,
                    static_cast<float>(Background.width),
                    static_cast<float>(Background.height)},
                   {0,
                    0,
                    static_cast<float>(g_ScreenWidth),
                    static_cast<float>(g_ScreenHeight)}, {0, 0}, 0, WHITE);
  }
  EndDrawing();
}

}



void Play::Play() {

  const bool Exit = false;
  const bool PlayerWon = false;

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input();
    Update();
    Draw();
  }

}
