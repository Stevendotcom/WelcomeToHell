#include "Demon.h"

#include <iostream>

#include "Constants.h"
#include "engine/ResManager.h"

namespace {

constexpr float k_Speed = 1000;

/**
 * 
 */
void DivideDemon() {
}

/**
 * 
 * @param Demon 
 * @return 
 */
Texture GetNextFrame(Demon::DemonType& Demon) {

}

void Kill(Demon::DemonType& Demon, std::list<Demon::DemonType>& Demons) {
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
      std::cerr << "Something went wrong at Demon.cpp:54" << '\n';
  }

  return Position;
}

float GetRadiusRandom() {

  enum class Radii {
    Big = 80,
    Mid = 50,
    Sml = 30
  };

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
      std::cerr << "Something went wrong at Demon.cpp:89" << '\n';
  }

  return Size;
}

}

void Demon::Initialize(std::list<DemonType>& Demons,
                       const Vector2& PlayerPosition) {
  const DemonType Demon = {
      GetRandomStart(),
      PlayerPosition,
      k_Speed,
      GetRadiusRandom(),
      GetTexture(ResManager::Resources::DemonSpriteMove),
      0
  };
  Demons.push_back(Demon);
}

void Demon::Update(
    std::list<DemonType>& Demons,
    float Delta) {
  //TODO it should handle all demons, including killing and divide when nec
}

void Demon::Draw(const std::list<DemonType>& Demons) {
}
