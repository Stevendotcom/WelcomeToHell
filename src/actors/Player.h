#pragma once
#include "engine/Collisions.h"
#include "engine/Math.h"

namespace Player {

struct PlayerType {
  float f_Acceleration;
  float f_Radius;
  float f_DefAccel;
  int f_Hearts;
  int f_Score;
  Vector2 f_Position;
  Vector2 f_Speed;
  Vector2 f_Direction;
  Texture f_Sprite;
  bool f_IsInvencible;
  bool f_IsPowerBoostActive;
};




void Initialize(PlayerType& Player);

void Accelerate(PlayerType& Player);

void Duplicate(const PlayerType& Player,
               PlayerType& Duplicated,
               Collisions::WhereCollides CollisionPlace);

void UpdateDuplicate(PlayerType& Player,
                     PlayerType& Duplicated,
                     Collisions::WhereCollides CollisionPlace,
                     bool& DuplicatedVisible);

void Update(PlayerType& Player, float Delta, bool IsDuplicated = false);

void Draw(const PlayerType& Player);
};
