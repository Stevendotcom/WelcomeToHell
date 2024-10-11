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

namespace Play {

void Play() {

  const bool Exit = false;
  const bool PlayerWon = false;

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input();
    Update();
    Draw();
  }

}

} // namespace Play
