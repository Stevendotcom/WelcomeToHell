#pragma once
#include "raylib.h"

namespace Mouse {

struct MouseType {
  Vector2 f_Position;
  Texture f_Sprite;
  float f_Radius;
};

void Initialize(MouseType& Mouse);

void Update(MouseType& Mouse);

void Draw(const MouseType& Mouse);

}
