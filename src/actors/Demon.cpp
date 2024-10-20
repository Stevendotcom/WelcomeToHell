#include "Demon.h"

#include <iostream>

#include "Constants.h"
#include "engine/Error.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

namespace {

constexpr float k_Speed = 1000;
constexpr int k_Rows = 2;
constexpr int k_Cols = 6;

float FrameTime = 0;



enum class Radii { Big = 80, Mid = 50, Sml = 30 };



void Kill(Demon::DemonType& Demon, std::list<Demon::DemonType>& Demons) {
  Demons.remove_if(Demon); //TODO CHECK
}



/**
 *
 */
void DivideDemon(Demon::DemonType& Demon, std::list<Demon::DemonType>& Demons) {
  Demon::DemonType NewDemon = Demon;

  if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Big))) {

    NewDemon.f_Radius = static_cast<float>(Radii::Mid);
    Demon.f_Radius = static_cast<float>(Radii::Mid);
    Demons.push_back(NewDemon);
  } else if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Mid))) {

    NewDemon.f_Radius = static_cast<float>(Radii::Sml);
    Demon.f_Radius = static_cast<float>(Radii::Sml);
    Demons.push_back(NewDemon);

  } else if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Sml))) {
    Kill(Demon, Demons);
  } else {
    Error::Unhandled(__LINE__, __FILE__);
  }

}



/**
 *
 * @param Demon
 * @return
 */
Demon::Frame GetNextFrame(Demon::DemonType& Demon) {
  const Demon::Frame NewFrame = {
      static_cast<float>(Demon.f_FrameIndex % k_Cols * (
                           Demon.f_Sprite.width / k_Cols)),
      static_cast<float>(
        Demon.f_FrameIndex > 6 ? Demon.f_Sprite.height / k_Rows : 0),
      static_cast<float>(Demon.f_Sprite.width / k_Cols),
      static_cast<float>(Demon.f_Sprite.height / k_Rows),};
  Demon.f_FrameIndex++;
  return NewFrame;
}



Vector2 GetRandomStart() {
  enum class Start {
    Up,
    Down,
    Left,
    Right
  };

  const Start Starting = static_cast<Start>(GetRandomValue(
      static_cast<int>(Start::Up), static_cast<int>(Start::Right)));
  Vector2 Position;

  switch (Starting) {

    case Start::Up:
      Position = {static_cast<float>(GetRandomValue(0, g_ScreenWidth)), 0};
      break;

    case Start::Down:
      Position = {static_cast<float>(GetRandomValue(0, g_ScreenWidth)),
                  static_cast<float>(g_ScreenHeight)};
      break;

    case Start::Left:
      Position = {0, static_cast<float>(GetRandomValue(0, g_ScreenHeight))};
      break;

    case Start::Right:
      Position = {static_cast<float>(g_ScreenWidth),
                  static_cast<float>(GetRandomValue(0, g_ScreenHeight))};
      break;

    default:
      Position = {0, 0};
      Error::Unhandled(__LINE__, __FILE__);
  }

  return Position;
}



float GetRadiusRandom() {

  float Size;

  switch (GetRandomValue(0, 2)) {
    case 0:
      Size = static_cast<float>(Radii::Big);
      break;
    case 1:
      Size = static_cast<float>(Radii::Mid);
      break;
    case 2:
      Size = static_cast<float>(Radii::Sml);
      break;
    default:
      Size = 0;
      Error::Unhandled(__LINE__, __FILE__);
  }

  return Size;
}

} // Private

void Demon::Initialize(std::list<DemonType>& Demons,
                       const Vector2& PlayerPosition) {
  DemonType Demon = {GetRandomStart(),
                     PlayerPosition,
                     k_Speed,
                     GetRadiusRandom(),
                     GetTexture(ResManager::Resources::DemonSpriteMove),
                     {},
                     0};
  Demon.f_Frame = {0,
                   0,
                   static_cast<float>(Demon.f_Sprite.width / k_Cols),
                   static_cast<float>(Demon.f_Sprite.height / k_Rows)};
  Demons.push_back(Demon);
}



void Demon::Update(std::list<DemonType>& Demons,
                   const Vector2& PlayerPosition,
                   const float Delta) {

  for (auto& Demon : Demons) {
    Demon.f_Direction = PlayerPosition;
    Demon.f_Position = {Demon.f_Speed * Delta * Demon.f_Direction.x,
                        Demon.f_Speed * Delta * Demon.f_Direction.y};
  }
}



void Demon::Draw(std::list<DemonType>& Demons) {
  constexpr float k_RotCorrection = 90.0F;
  constexpr float k_Scale = 2.0F;
  constexpr float k_Minute = 60.0F;

  for (auto& Demon : Demons) {

    if (FrameTime > k_Cols * k_Rows / k_Minute) {
      Demon.f_Frame = GetNextFrame(Demon);
      FrameTime = 0;
    }
    FrameTime += GetFrameTime();

    DrawTexturePro(Demon.f_Sprite, Demon.f_Frame,
                   {Demon.f_Position.x,
                    Demon.f_Position.y,
                    Demon.f_Radius * 2.0f,
                    Demon.f_Radius * 2.0f},
                   {Demon.f_Radius * k_Scale, Demon.f_Radius * k_Scale},
                   k_RotCorrection - Math::GetRotation(Demon.f_Direction),
                   WHITE);
  }
}
