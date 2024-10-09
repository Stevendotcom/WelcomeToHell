#include "StartUp.h"

#include "raylib.h"

extern enum class ScreenSize { Width, Height };

void StartUp::Start() {
  constexpr int kFPS = 60;

  InitWindow(static_cast<int>(ScreenSize::Width),
             static_cast<int>(ScreenSize::Height), "Welcome To Hell");

  SetTargetFPS(kFPS);
}
