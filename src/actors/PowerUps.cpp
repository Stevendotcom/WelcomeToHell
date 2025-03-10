#include "PowerUps.h"

#include <iostream>

#include "Constants.h"
#include "Player.h"
#include "engine/ResManager.h"


namespace {

using namespace PowerUps;

std::list<int> Targets;

int UniqueId = 0;

constexpr float k_SpeedBoostP = 1.1f;


void UsePower(Player::PlayerType& Player, const Powers Power) {

  constexpr int k_PointBoost = 100;

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
  return {static_cast<float>(GetRandomValue(1, g_ScreenWidth)),
          static_cast<float>(GetRandomValue(1, g_ScreenHeight))};
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
                      {16,
                       16},
                      Powers::PointsBoost,
                      {},
                      {},
                      0,
                      0,
                      UniqueId};

  switch (static_cast<Powers>(rand() % 3)) {
    case Powers::PointsBoost:
      NewPower.f_SpriteFrames = 6;
      NewPower.f_Sprite = GetTexture(ResManager::Resources::Diamond);
      break;

    case Powers::OneUp:
      NewPower.f_SpriteFrames = 6;
      NewPower.f_Sprite = GetTexture(ResManager::Resources::OneUp);
      break;

    case Powers::SpeedBoost:
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
      continue;
    }

    Animations::Update(Power.f_Frame, 1, Power.f_SpriteFrames,
                       Power.f_FrameIndex, Power.f_FrameTime, Delta, {
                           static_cast<float>(Power.f_Sprite.width),
                           static_cast<float>(Power.f_Sprite.height)});

  }
}


void PowerUps::Draw(const PowerUp& Pow) {

  constexpr float k_Scale = 2.0F;

  DrawTexturePro(Pow.f_Sprite, Pow.f_Frame, {Pow.f_Position.x,
                                             Pow.f_Position.y,
                                             Pow.f_Size.x * k_Scale * 2.0F,
                                             Pow.f_Size.y * k_Scale * 2.0F}, {
                     Pow.f_Size.x * k_Scale,
                     Pow.f_Size.y * k_Scale}, 0, WHITE);
}
