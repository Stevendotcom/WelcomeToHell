#pragma once
#include "engine/Math.h"

namespace Player {

struct Player {
  float f_Speed;
  float f_Radius;
  int f_Hearts;
  Vector2 f_Position;
  Vector2 f_Direction;
  Texture f_Sprite;

};



void Initialize(Player& Player);

};
