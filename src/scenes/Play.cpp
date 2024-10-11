#include "Play.h"

#include "raylib.h"

namespace {

void Input() {
}



void Update() {
}



void Draw() {
  BeginDrawing();
  {
    DrawTexture();
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
