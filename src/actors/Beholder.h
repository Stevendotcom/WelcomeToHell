#pragma once
#include <list>

#include "engine/Animations.h"

namespace Player {
struct PlayerType;
}
namespace Beholder {

struct BeholderType {
  Vector2 f_Position;
  Vector2 f_FuturePosition;
  Vector2 f_Direction;
  float f_Speed;
  float f_Radius;
  float f_FrameTime;
  Texture f_Sprite;
  Animations::Frame f_Frame;
  int f_FrameIndex;
  int f_Id;
};

void Execute(std::list<BeholderType>& Beholders);

void Clear(std::list<BeholderType>& Beholders);

void AddBeholder(std::list<BeholderType>& Beholders);

void Update(std::list<BeholderType>& Beholders,
            Player::PlayerType& Player,
            float Delta);

void Draw(const BeholderType& Beholder);

};
