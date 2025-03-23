#include "Beholder.h"

#include <iostream>

#include "Constants.h"
#include "Player.h"
#include "engine/Collisions.h"
#include "engine/ResManager.h"

namespace {
using namespace Beholder;

std::list<int> Targets;

int UniqueIds = 0;

const float k_DefSpeed = 600;
const float k_DefRad = 90;
const float k_SpawnMargin = 600;
const int k_Cols = 6;
const int k_Rows = 5;

}


void Beholder::Execute(std::list<BeholderType>& Beholders) {
  for (const auto Target : Targets) {

    // For clarity: lambda function that checks if id == Beholders.f_id
    Beholders.remove_if([&, Target](auto& Beholder) -> bool {
      if (Beholder.f_Id == Target) {
        return true;
      }
      return false;
    });
  }

  Targets.clear();
}


void Beholder::Clear(std::list<BeholderType>& Beholders) {
  Beholders.clear();
  Targets.clear();
}


void Beholder::AddBeholder(std::list<BeholderType>& Beholders) {
  BeholderType NewBeholder = {};
  Vector2 NewPos;
  Vector2 NewDir;

  if (GetRandomValue(0,1)) {
    //right
    NewPos = {g_ScreenWidth + k_SpawnMargin,
              static_cast<float>(GetRandomValue(1, g_ScreenHeight))};
    NewDir = {-1.0f,
              0};
  } else {
    //left
    NewPos = {- k_SpawnMargin - 1,
              static_cast<float>(GetRandomValue(1, g_ScreenHeight))};
    NewDir = {1.0f,
              0};
  }

  NewBeholder = {NewPos,
                 NewPos,
                 NewDir,
                 k_DefSpeed,
                 k_DefRad,
                 0,
                 GetTexture(ResManager::Resources::Beholder),
                 {},
                 0,
                 UniqueIds};
  Beholders.emplace_back(NewBeholder);
  UniqueIds++;
}


void Beholder::Update(std::list<BeholderType>& Beholders,
                      Player::PlayerType& Player,
                      const float Delta) {
  for (auto& Beholder : Beholders) {

    Beholder.f_FuturePosition.x += Beholder.f_Speed * Delta;

    if (Collisions::IsCircleCircle(Beholder.f_FuturePosition, Beholder.f_Radius,
                                   Player.f_Position, Player.f_Radius)) {
      Player.f_Hearts--;
      Player.f_IsInvencible = true;
      Targets.push_back(Beholder.f_Id);
      continue;
    }

    if (Beholder.f_FuturePosition.x - Beholder.f_Radius >= g_ScreenWidth + k_SpawnMargin ||
        Beholder.f_FuturePosition.x + Beholder.f_Radius <= -k_SpawnMargin) {

      Targets.push_back(Beholder.f_Id);
      continue;
    }

    Beholder.f_Position = Beholder.f_FuturePosition;

    Animations::Update(Beholder.f_Frame, k_Rows, k_Cols, Beholder.f_FrameIndex,
                       Beholder.f_FrameTime, Delta, {
                           static_cast<float>(Beholder.f_Sprite.width),
                           static_cast<float>(Beholder.f_Sprite.height)});
  }
}


void Beholder::Draw(const BeholderType& Beholder) {

  const float TextureAdjust = Beholder.f_Radius * 1.2f;
  DrawTexturePro(Beholder.f_Sprite, Beholder.f_Frame, {Beholder.f_Position.x,
                   Beholder.f_Position.y,
                   Beholder.f_Radius * 2.0F + TextureAdjust,
                   Beholder.f_Radius * 2.0F + TextureAdjust}, {
                     Beholder.f_Radius + TextureAdjust / 2,
                     Beholder.f_Radius + TextureAdjust / 2},
                 -Math::GetRotation(Beholder.f_Direction), WHITE);

#ifdef _DEBUG
  DrawCircleLinesV(Beholder.f_Position, Beholder.f_Radius, WHITE);
#endif

}
