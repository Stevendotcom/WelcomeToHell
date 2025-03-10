#include "Demon.h"

#include <iostream>
#include <list>

#include "raylib.h"

#include "Constants.h"
#include "engine/Collisions.h"
#include "engine/Error.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

using namespace Collisions;

namespace {

constexpr float k_Speed = 100;
constexpr int k_Rows = 2;
constexpr int k_Cols = 6;

float FrameTime = 0;
int UniqueId = 0;

std::list<int> Targets;


enum class Radii { Big = 80, Mid = 50, Sml = 30 };


Vector2 GetRandomStart() {
  enum class Start {
    Up,
    Down,
    Left,
    Right
  };

  const auto Starting = static_cast<Start>(GetRandomValue(
      static_cast<int>(Start::Up), static_cast<int>(Start::Right)));
  Vector2 Position;

  switch (Starting) {

    case Start::Up:
      Position = {static_cast<float>(GetRandomValue(0, g_ScreenWidth)),
                  0};
      break;

    case Start::Down:
      Position = {static_cast<float>(GetRandomValue(0, g_ScreenWidth)),
                  static_cast<float>(g_ScreenHeight)};
      break;

    case Start::Left:
      Position = {0,
                  static_cast<float>(GetRandomValue(0, g_ScreenHeight))};
      break;

    case Start::Right:
      Position = {static_cast<float>(g_ScreenWidth),
                  static_cast<float>(GetRandomValue(0, g_ScreenHeight))};
      break;

    default:
      Position = {0,
                  0};
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

void Demon::ChangeDirection(DemonType& Demon) {
  Demon.f_Direction = Math::Rotate(Demon.f_Direction,
                                   static_cast<float>(GetRandomValue(0, 180)));
}



void Demon::DivideDemon(DemonType& Demon, std::list<DemonType>& Demons) {
  DemonType NewDemon = Demon;

  if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Big))) {

    if (Demon.f_Duplicate) {
      delete Demon.f_Duplicate;
      Demon.f_Duplicate = nullptr;
      NewDemon.f_Duplicate = nullptr;
    }

    NewDemon.f_Radius = static_cast<float>(Radii::Mid);
    NewDemon.f_Id = UniqueId++;
    ChangeDirection(Demon);
    ChangeDirection(NewDemon);

    Demon.f_Radius = static_cast<float>(Radii::Mid);
    Demons.push_back(NewDemon);

  } else if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Mid))) {

    if (Demon.f_Duplicate) {
      delete Demon.f_Duplicate;
      Demon.f_Duplicate = nullptr;
      NewDemon.f_Duplicate = nullptr;

    }
    NewDemon.f_Radius = static_cast<float>(Radii::Sml);
    NewDemon.f_Id = UniqueId++;
    ChangeDirection(Demon);
    ChangeDirection(NewDemon);
    Demon.f_Radius = static_cast<float>(Radii::Sml);
    Demons.push_back(NewDemon);

  } else if (Math::IsEqual(Demon.f_Radius, static_cast<float>(Radii::Sml))) {
    Targets.push_back(Demon.f_Id);
    if (Demon.f_Duplicate) {
      delete Demon.f_Duplicate;
      Demon.f_Duplicate = nullptr;
    }

  } else {
    Error::Unhandled(__LINE__, __FILE__);
  }

}



void Demon::Initialize(std::list<DemonType>& Demons,
                       const Vector2& PlayerPosition) {

  DemonType Demon = {GetRandomStart(),
                     {0,
                      0},
                     k_Speed,
                     GetRadiusRandom(),
                     GetTexture(ResManager::Resources::DemonSpriteMove),
                     {},
                     0,
                     UniqueId,
                     nullptr};

  UniqueId++;

  const Vector2 Temp = Math::Subtract(PlayerPosition, Demon.f_Position);
  Demon.f_Direction = Math::Normalize(Temp, Math::GetMag(Temp));

  Demon.f_Frame = {0,
                   0,
                   static_cast<float>(Demon.f_Sprite.width / k_Cols),
                   static_cast<float>(Demon.f_Sprite.height / k_Rows)};

#ifdef _DEBUG
  std::cout << "Demon init. ID: " << Demon.f_Id << "\n";
#endif
  Demons.push_back(Demon);
}



void Demon::Duplicate(DemonType& Demon,
                      DemonType* Duplicated,
                      const WhereCollides CollisionPlace) {
  *Duplicated = Demon;
  Duplicated->f_Duplicate = nullptr;
  switch (CollisionPlace) {

    case WhereCollides::Up:
      Duplicated->f_Position = {Demon.f_Position.x,
                                g_ScreenHeight + Demon.f_Position.y};
      break;

    case WhereCollides::Down:
      Duplicated->f_Position = {Demon.f_Position.x,
                                Demon.f_Position.y - g_ScreenHeight};
      break;

    case WhereCollides::Right:
      Duplicated->f_Position = {Demon.f_Position.x - g_ScreenWidth,
                                Demon.f_Position.y};
      break;

    case WhereCollides::Left:
      Duplicated->f_Position = {g_ScreenWidth + Demon.f_Position.x,
                                Demon.f_Position.y};
      break;
  }
}



void Demon::Execute(std::list<DemonType>& Demons) {
  for (const auto Target : Targets) {

#ifdef _DEBUG
    std::cout << "Demon kill. ID: " << Target << "\n";
#endif

    // For clarity: lambda function that checks if id == Demon.f_id
    Demons.remove_if([&, Target](auto& Demon) -> bool {
      if (Demon.f_Id == Target) {
        delete Demon.f_Duplicate;
        return true;
      }
      return false;
    });
  }

  Targets.clear();
}



void Demon::UpdateDuplicate(DemonType& Demon,
                            DemonType* Duplicated,
                            const WhereCollides CollisionPlace) {
  bool ShouldDupRemove = false;

  Duplicated->f_Position.x += Duplicated->f_Speed * GetFrameTime() * Duplicated
      ->f_Direction.x;
  Duplicated->f_Position.y += Duplicated->f_Speed * GetFrameTime() * Duplicated
      ->f_Direction.y;

  // cases where the duplicate needs to disappear or get copied to player
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Demon.f_Position.y + Demon.f_Radius <= 0) {
        //if no longer visible
        Demon = *Duplicated;
        ShouldDupRemove = true;

      } else if (Demon.f_Position.y - Demon.f_Radius > 0) {
        // if return
        ShouldDupRemove = true;
      }
      break;

    case WhereCollides::Down:

      if (Demon.f_Position.y - Demon.f_Radius >= g_ScreenHeight) {
        Demon = *Duplicated;
        ShouldDupRemove = true;

      } else if (Demon.f_Position.y + Demon.f_Radius < g_ScreenHeight) {
        ShouldDupRemove = true;
      }
      break;

    case WhereCollides::Right:

      if (Demon.f_Position.x - Demon.f_Radius >= g_ScreenWidth) {
        Demon = *Duplicated;
        ShouldDupRemove = true;

      } else if (Demon.f_Position.x + Demon.f_Radius < g_ScreenWidth) {
        ShouldDupRemove = true;

      }
      break;

    case WhereCollides::Left:

      if (Demon.f_Position.x + Demon.f_Radius <= 0) {

        Demon = *Duplicated;
        ShouldDupRemove = true;

      } else if (Demon.f_Position.x - Demon.f_Radius > 0) {
        ShouldDupRemove = true;

      }
      break;
  }

  if (ShouldDupRemove) {
    delete Duplicated;
    Demon.f_Duplicate = nullptr;
  }
}



void Demon::Update(std::list<DemonType>& Demons, const float Delta) {

  for (DemonType& Demon : Demons) {
    Demon.f_Position.x += Demon.f_Speed * Delta * Demon.f_Direction.x;
    Demon.f_Position.y += Demon.f_Speed * Delta * Demon.f_Direction.y;

    if (Animations::Update(Demon.f_Frame, k_Rows, k_Cols, Demon.f_FrameIndex,
                           FrameTime, {static_cast<float>(Demon.f_Sprite.width),
                                       static_cast<float>(Demon.f_Sprite.
                                         height)})) {
      Demon.f_Frame.height *= Demon.f_Direction.x > 0.0F ? 1.0F : -1.0F;
    }
  }

}



void Demon::Draw(const DemonType& Demon) {
  constexpr float k_Scale = 2.0F;

  DrawTexturePro(Demon.f_Sprite, Demon.f_Frame, {Demon.f_Position.x,
                                                 Demon.f_Position.y,
                                                 Demon.f_Radius * k_Scale *
                                                 2.0F,
                                                 Demon.f_Radius * k_Scale *
                                                 2.0F}, {
                     Demon.f_Radius * k_Scale,
                     Demon.f_Radius * k_Scale},
                 -Math::GetRotation(Demon.f_Direction), WHITE);

#ifdef _DEBUG
  DrawCircleLinesV(Demon.f_Position, Demon.f_Radius,
                   Demon.f_Duplicate ? BLACK : WHITE);
#endif
}
