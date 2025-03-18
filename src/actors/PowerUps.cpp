#include "PowerUps.h"

#include <iostream>

#include "Constants.h"
#include "Player.h"
#include "engine/ResManager.h"


namespace {

using namespace PowerUps;

std::list<int> Targets;

int UniqueId = 0;

constexpr int k_Size = 64;


void UsePower(Player::PlayerType& Player, const Powers Power) {

  constexpr int k_PointBoost = 1000;
  constexpr float k_SpeedBoostP = 2.5f;

  switch (Power) {
    case Powers::PointsBoost:
      Player.f_Score += k_PointBoost;
      break;

    case Powers::OneUp:
      if (Player.f_Hearts < 3) {
        Player.f_Hearts++;
      }
      break;

    case Powers::SpeedBoost:
      if (!Player.f_IsPowerBoostActive) {
        Player.f_IsPowerBoostActive = true;
        Player.f_Acceleration *= k_SpeedBoostP;
      }
      break;
  }
}


Vector2 GetRandomPos() {
  return {static_cast<float>(GetRandomValue(1, g_ScreenWidth - k_Size)),
          static_cast<float>(GetRandomValue(1, g_ScreenHeight - k_Size))};
}

}


void PowerUps::Execute(std::list<PowerUp>& PowerUps) {
  for (const auto Target : Targets) {

#ifdef _DEBUG
    std::cout << "Power kill. ID: " << Target << "\n";
#endif

    // For clarity: lambda function that checks if id == Demon.f_id
    PowerUps.remove_if([&, Target](auto& Power) -> bool {
      return Power.f_Id == Target;
    });
  }

  Targets.clear();
}


void PowerUps::AddPower(std::list<PowerUp>& Pows) {
  PowerUp NewPower = {GetRandomPos(),
                      {k_Size,
                       k_Size},
                      Powers::PointsBoost,
                      {},
                      {},
                      0,
                      0,
                      UniqueId,
                      0};

  switch (static_cast<Powers>(GetRandomValue(0, 2))) {
    case Powers::PointsBoost:
      NewPower.f_SpriteFrames = 6;
      NewPower.f_Sprite = GetTexture(ResManager::Resources::Diamond);
      break;

    case Powers::OneUp:
      NewPower.f_Power = Powers::OneUp;
      NewPower.f_SpriteFrames = 6;
      NewPower.f_Sprite = GetTexture(ResManager::Resources::OneUp);
      break;

    case Powers::SpeedBoost:
      NewPower.f_Power = Powers::SpeedBoost;
      NewPower.f_SpriteFrames = 1;
      NewPower.f_Sprite = GetTexture(ResManager::Resources::Batteries);
      break;
  }
  Pows.emplace_back(NewPower);
  UniqueId++;
}


void PowerUps::Update(std::list<PowerUp>& Powers,
                      Player::PlayerType& Player,
                      const float Delta) {

  for (auto& Power : Powers) {

    if (Collisions::IsCircleSquare(Player.f_Position, Player.f_Radius,
                                   Power.f_Position, Power.f_Size)) {
      Targets.push_back(Power.f_Id);
      UsePower(Player, Power.f_Power);
    }

    Animations::Update(Power.f_Frame, 1, Power.f_SpriteFrames,
                       Power.f_FrameIndex, Power.f_FrameTime, Delta, {
                           static_cast<float>(Power.f_Sprite.width),
                           static_cast<float>(Power.f_Sprite.height)});

  }
}


void PowerUps::Draw(const PowerUp& Power) {

  DrawTexturePro(Power.f_Sprite, Power.f_Frame, {Power.f_Position.x,
                                                 Power.f_Position.y,
                                                 Power.f_Size.x,
                                                 Power.f_Size.y}, {0,
                   0}, 0, WHITE);

#ifdef _DEBUG
  DrawRectangleLines(static_cast<int>(Power.f_Position.x),
                     static_cast<int>(Power.f_Position.y),
                     static_cast<int>(Power.f_Size.x),
                     static_cast<int>(Power.f_Size.y), WHITE);
#endif

}
