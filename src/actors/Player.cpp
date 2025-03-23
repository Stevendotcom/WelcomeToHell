#include "Player.h"

#include "raylib.h"

#include "Constants.h"
#include "Mouse.h"
#include "engine/Collisions.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

using namespace Math;
using namespace Collisions;

namespace {

constexpr float k_MaxSpeed = 500.0F;
constexpr float k_DefRadius = 40.0F;
constexpr float k_DefAccel = 1000.0F;
constexpr int k_DefHearts = 3;

}


void Player::Initialize(PlayerType& Player) {
  Player = {k_DefAccel,
            k_DefRadius,
            k_DefAccel,
            0,
            k_DefHearts,
            0,
            0,
            {g_ScreenWidth / 2.0F,
             g_ScreenHeight / 2.0F},
            {0.0F,
             0.0F},
            {0.0F,
             -1.0F},
            {},
            GetTexture(ResManager::Resources::PlayerSprite),
            GetTexture(ResManager::Resources::FireSmall),
            {},
            false,
            false};
}



void Player::Accelerate(PlayerType& Player) {
  Player.f_Speed = Add(Player.f_Speed,
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
      Duplicated.f_Position = {Player.f_Position.x,
                               g_ScreenHeight + Player.f_Position.y};
      break;

    case WhereCollides::Down:
      Duplicated.f_Position = {Player.f_Position.x,
                               Player.f_Position.y - g_ScreenHeight};
      break;

    case WhereCollides::Right:
      Duplicated.f_Position = {Player.f_Position.x - g_ScreenWidth,
                               Player.f_Position.y};
      break;

    case WhereCollides::Left:
      Duplicated.f_Position = {g_ScreenWidth + Player.f_Position.x,
                               Player.f_Position.y};
      break;
  }
}



void Player::UpdateDuplicate(PlayerType& Player,
                             PlayerType& Duplicated,
                             const WhereCollides CollisionPlace,
                             bool& DuplicatedVisible) {
  Duplicated = {Player.f_Acceleration,
                Player.f_Radius,
                Player.f_Acceleration,
                Player.f_FrameTime,
                Player.f_Hearts,
                Player.f_Score,
                Player.f_FrameIndex,
                Duplicated.f_Position,
                Player.f_Speed,
                Player.f_Direction,
                Player.f_JetpackEndPosition,
                Player.f_Sprite,
                Player.f_SpriteFire,
                Player.f_Frame,
                Player.f_IsInvencible,
                Player.f_IsPowerBoostActive};

  Update(Duplicated, GetFrameTime(), true);

  // cases where the duplicate needs to disappear or get copied to player
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Player.f_Position.y + Player.f_Radius <= 0) {
        //if no longer visible
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_Position.y - Player.f_Radius > 0) {
        // if return
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Down:

      if (Player.f_Position.y - Player.f_Radius >= g_ScreenHeight) {
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_Position.y + Player.f_Radius < g_ScreenHeight) {
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Right:

      if (Player.f_Position.x - Player.f_Radius >= g_ScreenWidth) {
        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_Position.x + Player.f_Radius < g_ScreenWidth) {
        DuplicatedVisible = false;
      }
      break;

    case WhereCollides::Left:

      if (Player.f_Position.x + Player.f_Radius <= 0) {

        Player = Duplicated;
        DuplicatedVisible = false;
      } else if (Player.f_Position.x - Player.f_Radius > 0) {
        DuplicatedVisible = false;
      }
      break;
  }
}



void Player::Update(PlayerType& Player,
                    const float Delta,
                    const bool IsDuplicated) {

  const Vector2 MousePos = GetMousePosition();

  if (!IsDuplicated) {

    const Vector2 k_Temp = {MousePos.x - Player.f_Position.x,
                            MousePos.y - Player.f_Position.y};

    const float k_Mag = GetMag(k_Temp);

    Player.f_Direction = Normalize(k_Temp, k_Mag);
  }

  Player.f_Position = {Player.f_Position.x + Player.f_Speed.x * Delta,
                       Player.f_Position.y + Player.f_Speed.y * Delta};

  Player.f_JetpackEndPosition = {
      (Player.f_Direction.x * -(Player.f_Radius + 64) + Player.f_Position.x),
      (Player.f_Direction.y * -(Player.f_Radius + 64) + Player.f_Position.y)};

  Player.f_SpriteFire = GetTexture(Mouse::IsAccelerating()
                                     ? ResManager::Resources::FireBig
                                     : ResManager::Resources::FireSmall);

  Animations::Update(Player.f_Frame, 1, 14, Player.f_FrameIndex,
                     Player.f_FrameTime, Delta, {
                         static_cast<float>(Player.f_SpriteFire.width),
                         static_cast<float>(Player.f_SpriteFire.height)});
}



void Player::Draw(const PlayerType& Player) {
  constexpr float k_RotCorrection = 90.0F;
  constexpr float k_Scale = 2.0F;
  constexpr float k_FireFrames = 14.0F;

  const Rectangle k_Source = {0,
                            0,
                            static_cast<float>(Player.f_Sprite.width),
                            static_cast<float>(Player.f_Sprite.height)};

  const Rectangle k_Dest = {Player.f_Position.x,
                          Player.f_Position.y,
                          Player.f_Radius * k_Scale * 2.0F,
                          Player.f_Radius * k_Scale * 2.0F};

  DrawTexturePro(Player.f_Sprite, k_Source, k_Dest, {Player.f_Radius * k_Scale,
                                                 Player.f_Radius * k_Scale},
                 k_RotCorrection - GetRotation(Player.f_Direction),
                 Player.f_IsInvencible ? RED : WHITE);

  DrawTexturePro(Player.f_SpriteFire, Player.f_Frame, {
                     Player.f_JetpackEndPosition.x,
                     Player.f_JetpackEndPosition.y,
                     (Player.f_SpriteFire.width / k_FireFrames) * 2,
                     static_cast<float>(Player.f_SpriteFire.height) * 2}, {
                     (Player.f_SpriteFire.width / k_FireFrames),
                     static_cast<float>(Player.f_SpriteFire.height)},
                 -GetRotation({Player.f_Direction.x * -1,
                              Player.f_Direction.y * -1}) + 90.0f, WHITE);

#ifdef _DEBUG
  DrawCircleLinesV(Player.f_Position, Player.f_Radius,WHITE);
#endif
}
