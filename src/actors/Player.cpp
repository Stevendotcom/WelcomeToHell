#include "Player.h"

#include "Constants.h"
#include "engine/ResManager.h"

using namespace Math;

namespace {

constexpr float k_MaxSpeed = 500.0F;
constexpr float k_DefRadius = 90.0F;
constexpr int k_DefHearts = 3;
constexpr int k_DefAccel = 10.0F;

}



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
  float k_SpeedMag;

  Player.f_Direction = Normalize(k_Temp, k_Mag);

  Player.f_Speed = Add(Player.f_Speed,
                       Multiply(Player.f_Direction, Player.f_Acceleration));

  if (Player.f_Speed.x * Player.f_Speed.x + Player.f_Speed.y * Player.f_Speed.y
      > k_MaxSpeed * k_MaxSpeed) {

    k_SpeedMag = GetMag(Player.f_Speed);

    Player.f_Speed = Normalize(Player.f_Speed, k_SpeedMag);
    Player.f_Speed = Multiply(Player.f_Speed, k_MaxSpeed);
  }

}



void Player::Input(PlayerType& Player, const float Pause) {
  if (!Pause && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Accelerate(Player, GetMousePosition());
  }
}



void Player::Update(PlayerType& Player, float Delta) {
  Player.f_PositionCenter = {
      Player.f_PositionCenter.x + Player.f_Speed.x * Delta,
      Player.f_PositionCenter.y + Player.f_Speed.y * Delta};
}



void Player::Draw(const PlayerType& Player) {
  constexpr float k_RotCorrection = 90.0f;

  const Rectangle Source = {0,
                            0,
                            static_cast<float>(Player.f_Sprite.width),
                            static_cast<float>(Player.f_Sprite.height)};
  const Rectangle Dest = {Player.f_PositionCenter.x,
                          Player.f_PositionCenter.y,
                          Player.f_Radius * 2.0f,
                          Player.f_Radius * 2.0f};

  DrawTexturePro(Player.f_Sprite, Source, Dest,
                 {Player.f_Radius, Player.f_Radius},
                 k_RotCorrection - GetRotation(Player.f_Direction), WHITE);

}
