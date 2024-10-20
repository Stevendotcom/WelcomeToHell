﻿#include "Player.h"

#include "Constants.h"
#include "raylib.h"
#include "engine/Collisions.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

using namespace Math;
using namespace Collisions;

namespace {

constexpr float k_MaxSpeed = 500.0F;
constexpr float k_DefRadius = 40.0F;
constexpr int k_DefHearts = 3;
constexpr int k_DefAccel = 1000.0F;

} // namespace

void Player::Initialize(PlayerType& Player) {
  Player = {k_DefAccel,
            k_DefRadius,
            k_DefHearts,
            {g_ScreenWidth / 2.0F, g_ScreenHeight / 2.0F},
            {0.0F, 0.0F},
            {0.0F, -1.0F},
            GetTexture(ResManager::Resources::PlayerSprite)};
}



void Player::Accelerate(PlayerType& Player) {
  Player.f_Speed =
      Add(Player.f_Speed,
                       Multiply(Player.f_Direction,
                                Player.f_Acceleration * GetFrameTime()));

  if (Player.f_Speed.x * Player.f_Speed.x + Player.f_Speed.y * Player.f_Speed.y
      > k_MaxSpeed * k_MaxSpeed) {

    Player.f_Speed = Normalize(Player.f_Speed, GetMag(Player.f_Speed));
    Player.f_Speed = Multiply(Player.f_Speed, k_MaxSpeed);
  }
}



void Player::Duplicate(const PlayerType& Player,
                       PlayerType& Duplicated,
                       const WhereCollides CollisionPlace) {

  switch (CollisionPlace) {

    case WhereCollides::Up:
      Duplicated.f_PositionCenter = {Player.f_PositionCenter.x,
                                     g_ScreenHeight + Player.f_PositionCenter.
                                     y};
      break;

    case WhereCollides::Down:
      Duplicated.f_PositionCenter = {Player.f_PositionCenter.x,
                                     Player.f_PositionCenter.y -
                                     g_ScreenHeight};
      break;

    case WhereCollides::Right:
      Duplicated.f_PositionCenter = {Player.f_PositionCenter.x - g_ScreenWidth,
                                     Player.f_PositionCenter.y};
      break;

    case WhereCollides::Left:
      Duplicated.f_PositionCenter = {g_ScreenWidth + Player.f_PositionCenter.x,
                                     Player.f_PositionCenter.y};
      break;
  }
}



void Player::UpdateDuplicate(PlayerType& Player,
                             PlayerType& Duplicated,
                             const WhereCollides CollisionPlace,
                             bool& DuplicatedVisible) {
  Duplicated = {Player.f_Acceleration,
                Player.f_Radius,
                Player.f_Hearts,
                Duplicated.f_PositionCenter,
                Player.f_Speed,
                Player.f_Direction,
                Player.f_Sprite};

  Update(Duplicated, GetFrameTime(), true);

  // cases where the duplicate needs to disappear or get copied to player
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Player.f_PositionCenter.y + Player.f_Radius <= 0) {
        //if no longer visible
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_PositionCenter.y - Player.f_Radius > 0) {
        // if return
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Down:

      if (Player.f_PositionCenter.y - Player.f_Radius >= g_ScreenHeight) {
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_PositionCenter.y + Player.f_Radius < g_ScreenHeight) {
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Right:

      if (Player.f_PositionCenter.x - Player.f_Radius >= g_ScreenWidth) {
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_PositionCenter.x + Player.f_Radius < g_ScreenWidth) {
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Left:

      if (Player.f_PositionCenter.x + Player.f_Radius <= 0) {

        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_PositionCenter.x - Player.f_Radius > 0) {
        DuplicatedVisible = false;
      }
      break;
  }
}



void Player::Input(PlayerType& Player, const bool Pause) {
  if (!Pause && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Accelerate(Player);
  }
}



void Player::Update(PlayerType& Player, const float Delta, bool IsDuplicated) {
  if (!IsDuplicated) {

    const Vector2 k_Temp = {GetMousePosition().x - Player.f_PositionCenter.x,
                            GetMousePosition().y - Player.f_PositionCenter.y};

    const float k_Mag = GetMag(k_Temp);

    Player.f_Direction = Normalize(k_Temp, k_Mag);
  }
  Player.f_PositionCenter = {
      Player.f_PositionCenter.x + Player.f_Speed.x * Delta,
      Player.f_PositionCenter.y + Player.f_Speed.y * Delta};
}



void Player::Draw(const PlayerType& Player) {
  constexpr float k_RotCorrection = 90.0F;
  constexpr float k_Scale = 2.0F;
  const Rectangle Source = {0,
                            0,
                            static_cast<float>(Player.f_Sprite.width),
                            static_cast<float>(Player.f_Sprite.height)};

  const Rectangle Dest = {Player.f_PositionCenter.x,
                          Player.f_PositionCenter.y,
                          Player.f_Radius * k_Scale * 2.0F,
                          Player.f_Radius * k_Scale * 2.0F};

  DrawTexturePro(Player.f_Sprite, Source, Dest,
                 {Player.f_Radius * k_Scale, Player.f_Radius * k_Scale},
                 k_RotCorrection - GetRotation(Player.f_Direction), WHITE);
}
