#include "Player.h"

#include "Constants.h"
#include "raylib.h"
#include "engine/Collisions.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

using namespace Math;
using namespace Collisions;

namespace {

constexpr float k_MaxSpeed = 500.0F;
constexpr float k_DefRadius = 90.0F;
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



void Player::Accelerate(PlayerType& Player, const Vector2& MousePosition) {

  const Vector2 k_Temp = {MousePosition.x - Player.f_PositionCenter.x,
                          MousePosition.y - Player.f_PositionCenter.y};

  const float k_Mag = GetMag(k_Temp);

  Player.f_Direction = Normalize(k_Temp, k_Mag);

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
  Duplicated.f_Acceleration = Player.f_Acceleration;
  Duplicated.f_Speed = Player.f_Speed;
  Duplicated.f_Radius = Player.f_Radius;
  Duplicated.f_Hearts = Player.f_Hearts;
  Duplicated.f_Sprite = Player.f_Sprite;

  switch (CollisionPlace) {

    case WhereCollides::Up:
      Duplicated.f_PositionCenter = {Player.f_PositionCenter.x, g_ScreenHeight};
      break;

    case WhereCollides::Down:
      Duplicated.f_PositionCenter = {Player.f_PositionCenter.x, 0};
      break;

    case WhereCollides::Right:
      Duplicated.f_PositionCenter = {0, Player.f_PositionCenter.y};
      break;

    case WhereCollides::Left:
      Duplicated.f_PositionCenter = {g_ScreenWidth, Player.f_PositionCenter.y};
      break;
  }
}



void Player::UpdateDuplicate(PlayerType& Player,
                             PlayerType& Duplicated,
                             const WhereCollides CollisionPlace,
                             bool& DuplicatedVisible) {
  Duplicated.f_Hearts = Player.f_Hearts;
  Player::Input(Duplicated, false);
  Player::Update(Duplicated, GetFrameTime());
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Player.f_PositionCenter.y - Player.f_Radius <= -Player.f_Radius) {
        Player = Duplicated;
        DuplicatedVisible = false;
        // Todo Delete duplicate
      }
      break;

    case WhereCollides::Down:
      if (Player.f_PositionCenter.y + Player.f_Radius >= g_ScreenHeight + Player
          .f_Radius) {
        Player = Duplicated;
        DuplicatedVisible = false;
        // Todo Delete duplicate
      }
      break;

    case WhereCollides::Right:
      if (Player.f_PositionCenter.y + Player.f_Radius >= g_ScreenWidth + Player.
          f_Radius) {

        Player = Duplicated;
        DuplicatedVisible = false;
        // Todo Delete duplicate
      }
      break;

    case WhereCollides::Left:
      if (Player.f_PositionCenter.y - Player.f_Radius >= -Player.f_Radius) {

        Player = Duplicated;
        DuplicatedVisible = false;
        // Todo Delete duplicate
      }
      break;
  }
}



void Player::Input(PlayerType& Player, const bool Pause) {
  if (!Pause && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Accelerate(Player, GetMousePosition());
  }
}



void Player::Update(PlayerType& Player, const float Delta) {
  Player.f_PositionCenter = {
      Player.f_PositionCenter.x + Player.f_Speed.x * Delta,
      Player.f_PositionCenter.y + Player.f_Speed.y * Delta};
}



void Player::Draw(const PlayerType& Player) {
  constexpr float k_RotCorrection = 90.0F;

  const Rectangle Source = {0,
                            0,
                            static_cast<float>(Player.f_Sprite.width),
                            static_cast<float>(Player.f_Sprite.height)};

  const Rectangle Dest = {Player.f_PositionCenter.x,
                          Player.f_PositionCenter.y,
                          Player.f_Radius * 2.0F,
                          Player.f_Radius * 2.0F};

  DrawTexturePro(Player.f_Sprite, Source, Dest,
                 {Player.f_Radius, Player.f_Radius},
                 k_RotCorrection - GetRotation(Player.f_Direction), WHITE);
}
