#include "Play.h"

#include "raylib.h"
#include "engine/ResManager.h"

namespace {

void Input() {
}



void Update() {
}



void Draw() {
  BeginDrawing();
  {
    DrawTexture(GetTexture(ResManager::Resources::Background), 0, 0, WHITE);
  }
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
