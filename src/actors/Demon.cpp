#include "Demon.h"

#include <iostream>

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



enum class Radii { Big = 80, Mid = 50, Sml = 30 };



void Kill(std::list<Demon::DemonType>& Demons, const int Id) {

#ifdef _DEBUG
  std::cout << "Demon kill. ID: " << Id << "\n";
#endif

  // For clarity: lambda function that checks if id == Demon.f_id
  Demons.remove_if([&, Id](auto& Demon) -> bool {
    return Demon.f_Id == Id;
  });

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
    Kill(Demons, Demon.f_Id);
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
                     {0, 0},
                     k_Speed,
                     GetRadiusRandom(),
                     GetTexture(ResManager::Resources::DemonSpriteMove),
                     {},
                     0,
                     UniqueId,
                     false,
                     nullptr};

  UniqueId++;

  Vector2 Temp = Math::Subtract(PlayerPosition, Demon.f_Position);
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



void Demon::Duplicate(const DemonType& Demon,
                      DemonType& Duplicated,
                      const WhereCollides CollisionPlace) {
  Duplicated = Demon;

  switch (CollisionPlace) {

    case WhereCollides::Up:
      Duplicated.f_Position = {Demon.f_Position.x,
                               g_ScreenHeight + Demon.f_Position.y};
      break;

    case WhereCollides::Down:
      Duplicated.f_Position = {Demon.f_Position.x,
                               Demon.f_Position.y - g_ScreenHeight};
      break;

    case WhereCollides::Right:
      Duplicated.f_Position = {Demon.f_Position.x - g_ScreenWidth,
                               Demon.f_Position.y};
      break;

    case WhereCollides::Left:
      Duplicated.f_Position = {g_ScreenWidth + Demon.f_Position.x,
                               Demon.f_Position.y};
      break;
  }
}



void Demon::UpdateDuplicate(DemonType& Demon,
                            DemonType& Duplicated,
                            const WhereCollides CollisionPlace,
                            bool& DuplicatedVisible,
                            std::list<DemonType>& DemonDups) {

  Duplicated.f_Position.x += Duplicated.f_Speed * GetFrameTime() * Duplicated.
      f_Direction.x;
  Duplicated.f_Position.y += Duplicated.f_Speed * GetFrameTime() * Duplicated.
      f_Direction.y;

  // cases where the duplicate needs to disappear or get copied to player
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Demon.f_Position.y + Demon.f_Radius <= 0) {
        //if no longer visible
        Demon = Duplicated;
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;
      } else if (Demon.f_Position.y - Demon.f_Radius > 0) {
        // if return
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      }
      break;

    case WhereCollides::Down:

      if (Demon.f_Position.y - Demon.f_Radius >= g_ScreenHeight) {
        Demon = Duplicated;
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      } else if (Demon.f_Position.y + Demon.f_Radius < g_ScreenHeight) {
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      }
      break;

    case WhereCollides::Right:

      if (Demon.f_Position.x - Demon.f_Radius >= g_ScreenWidth) {
        Demon = Duplicated;
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      } else if (Demon.f_Position.x + Demon.f_Radius < g_ScreenWidth) {
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      }
      break;

    case WhereCollides::Left:

      if (Demon.f_Position.x + Demon.f_Radius <= 0) {

        Demon = Duplicated;
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      } else if (Demon.f_Position.x - Demon.f_Radius > 0) {
        DuplicatedVisible = false;
        Kill(DemonDups, Duplicated.f_Id);
        Demon.f_Duplicate = nullptr;

      }
      break;
  }
}



void Demon::Update(std::list<DemonType>& Demons, const float Delta) {

  for (DemonType& Demon : Demons) {
    Demon.f_Position.x += Demon.f_Speed * Delta * Demon.f_Direction.x;
    Demon.f_Position.y += Demon.f_Speed * Delta * Demon.f_Direction.y;

  }

}



void Demon::Draw(std::list<DemonType>& Demons) {
  constexpr float k_RotCorrection = 0.0F;
  constexpr float k_Scale = 2.0F;
  constexpr float k_Minute = 60.0F;

  for (auto& Demon : Demons) {

    if (FrameTime > k_Cols * k_Rows / k_Minute) {
      Demon.f_Frame = GetNextFrame(Demon);
      Demon.f_Frame.height *= (Demon.f_Direction.x > 0.0F ? 1.0f : -1.0f);
      FrameTime = 0;
    }
    FrameTime += GetFrameTime();

    DrawTexturePro(Demon.f_Sprite, Demon.f_Frame,
                   {Demon.f_Position.x,
                    Demon.f_Position.y,
                    Demon.f_Radius * 2.0f,
                     Demon.f_Radius * 2.0f},
                   {Demon.f_Radius * k_Scale,
                     Demon.f_Radius * k_Scale},
                   k_RotCorrection - Math::GetRotation(Demon.f_Direction),
                   WHITE);
  }
}
