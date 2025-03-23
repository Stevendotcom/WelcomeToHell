#pragma once
#include "engine/Animations.h"
#include "engine/Collisions.h"

namespace Player {

struct PlayerType {
  float f_Acceleration;
  float f_Radius;
  float f_DefAccel;
  float f_FrameTime;
  int f_Hearts;
  int f_Score;
  int f_FrameIndex;
  Vector2 f_Position;
  Vector2 f_Speed;
  Vector2 f_Direction;
  Vector2 f_JetpackEndPosition;
  Texture f_Sprite;
  Texture f_SpriteFire;
  Animations::Frame f_Frame;
  bool f_IsInvencible;
  bool f_IsPowerBoostActive;
  bool f_IsAccelerating;
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
