#include "Play.h"

#include "raylib.h"

namespace Play {

#pragma region Declarations

void Input();
void Update();
void Draw();

#pragma endregion

void Play() {

  bool exit = false;
  bool playerWon = false;

  while (!exit && !playerWon && !WindowShouldClose()) {
    Input();
    Update();
    Draw();
  }

}

void Input() {
}

void Update() {
}

void Draw() {
}

} // namespace Play
