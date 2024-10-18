#include "Demon.h"

#include <iostream>

#include "Constants.h"

namespace {

constexpr

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

  const Start Starting = static_cast<Start>(GetRandomValue(static_cast<int>(Start::Up), static_cast<int>(Start::Right)));
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
}

void Demon::Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition) {

}

void Demon::Update(
    std::list<DemonType>& Demons,
    float Delta) {
  //TODO it should handle all demons, including killing and divide when nec
}

void Demon::Draw(const std::list<DemonType>& Demons) {
}
