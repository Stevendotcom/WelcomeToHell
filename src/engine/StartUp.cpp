#include "StartUp.h"

#include "Constants.h"
#include "raylib.h"

void StartUp::Start() {
  constexpr int kFPS = 60;

  InitWindow(gScreenWidth, gScreenHeight, "Welcome To Hell");

  SetTargetFPS(kFPS);
}
