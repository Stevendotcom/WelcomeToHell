#pragma once
#include <list>

#include "raylib.h"

#include "Player.h"
#include "engine/Animations.h"

namespace PowerUps {

enum class Powers {
  PointsBoost,
  OneUp,
  SpeedBoost
};

struct PowerUp {
  Vector2 f_Position;
  Vector2 f_Size;
  Powers f_Power;
  Texture f_Sprite;
  Animations::Frame f_Frame;
  int f_SpriteFrames;
  int f_FrameIndex;
  int f_Id;
  float f_FrameTime;
};

void Execute(std::list<PowerUp>& PowerUps);

void AddPower(std::list<PowerUp>& Pows);

void Update(std::list<PowerUp>& Powers, Player::PlayerType& Player, float Delta);

void Draw(const PowerUp& Power);

}
