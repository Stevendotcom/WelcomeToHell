#include "Bullet.h"

#include <iostream>
#include <list>

#include "raylib.h"

#include "Constants.h"
#include "engine/Collisions.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

using namespace Collisions;

namespace {

std::list<int> Targets;

constexpr float k_Speed = 1000.0F;
constexpr float k_Width = 30.0F;
constexpr size_t k_AmountMax = 100;
int UniqueId = 0;



enum {
  e_Front,
  e_Back,
};

}


void Bullet::AddToTargets(const int Id) {
  Targets.push_back(Id);
}



void Bullet::Execute(std::list<BulletType>& Bullets) {
  for (const auto Target : Targets) {

#ifdef _DEBUG
    std::cout << "Bullet kill. ID: " << Target << "\n";
#endif

    // For clarity: lambda function that checks if id == Bullet.f_id
    Bullets.remove_if([&, Target](auto& Bullet) -> bool {
      return Bullet.f_Id == Target;
    });
  }
  Targets.clear();
}


void Bullet::Clear(std::list<BulletType>& Bullets) {
  for (const auto Bullet : Bullets) {
    delete Bullet.f_Duplicate;
  }
  Bullets.clear();
}



void Bullet::Shoot(std::list<BulletType>& Bullets,
                   const Vector2& PlayerDirection,
                   const float PlayerRadius,
                   const Vector2& PlayerPosition) {

  const BulletType Bullet = {PlayerDirection,
                             {Math::Add(
                                  Math::Multiply(
                                      PlayerDirection, k_Width + PlayerRadius),
                                  PlayerPosition),
                              Math::Add(
                                  Math::Multiply(PlayerDirection, PlayerRadius),
                                  PlayerPosition)},
                             k_Speed,
                             GetTexture(ResManager::Resources::BulletSprite),
                             nullptr,
                             UniqueId};

  if (Bullets.size() < k_AmountMax) {

    UniqueId++;

    PlaySound(GetSound(ResManager::Resources::Shoot));

    Bullets.push_back(Bullet);
  }
}



void Bullet::UpdateDuplicate(BulletType& Bullet,
                             BulletType* Duplicated,
                             const WhereCollides CollisionPlace) {

  bool ShouldDupRemove = false;
  const float Resultant = Duplicated->f_Speed * GetFrameTime();

  Duplicated->f_Vectors[e_Front].x += Resultant * Duplicated->f_Direction.x;
  Duplicated->f_Vectors[e_Front].y += Resultant * Duplicated->f_Direction.y;
  Duplicated->f_Vectors[e_Back].x += Resultant * Duplicated->f_Direction.x;
  Duplicated->f_Vectors[e_Back].y += Resultant * Duplicated->f_Direction.y;

  // cases where the duplicate needs to disappear or get copied to player
  switch (CollisionPlace) {

    case WhereCollides::Up:
      if (Bullet.f_Vectors[e_Back].y <= 0) {
        //if no longer visible
        Bullet = *Duplicated;
        ShouldDupRemove = true;

      }
      break;

    case WhereCollides::Down:

      if (Bullet.f_Vectors[e_Back].y >= g_ScreenHeight) {
        Bullet = *Duplicated;
        ShouldDupRemove = true;

      }
      break;

    case WhereCollides::Right:

      if (Bullet.f_Vectors[e_Back].x >= g_ScreenWidth) {
        Bullet = *Duplicated;
        ShouldDupRemove = true;

      }
      break;

    case WhereCollides::Left:

      if (Bullet.f_Vectors[e_Back].x <= 0) {

        Bullet = *Duplicated;
        ShouldDupRemove = true;

      }
      break;
  }

  if (ShouldDupRemove) {
    delete Duplicated;
    Bullet.f_Duplicate = nullptr;
  }

}



void Bullet::Duplicate(const BulletType& Bullet,
                       BulletType* Duplicated,
                       const WhereCollides CollisionPlace) {
  *Duplicated = Bullet;

  switch (CollisionPlace) {
    case WhereCollides::Up:
      Duplicated->f_Vectors[e_Front] = {Bullet.f_Vectors[e_Front].x,
                                        g_ScreenHeight + Bullet.f_Vectors[
                                          e_Front].y};
      Duplicated->f_Vectors[e_Back] = {Bullet.f_Vectors[e_Back].x,
                                       g_ScreenHeight + Bullet.f_Vectors[e_Back]
                                       .y};
      break;

    case WhereCollides::Down:
      Duplicated->f_Vectors[e_Front] = {Bullet.f_Vectors[e_Front].x,
                                        Bullet.f_Vectors[e_Front].y -
                                        g_ScreenHeight};

      Duplicated->f_Vectors[e_Back] = {Bullet.f_Vectors[e_Back].x,
                                       Bullet.f_Vectors[e_Back].y -
                                       g_ScreenHeight};
      break;

    case WhereCollides::Right:
      Duplicated->f_Vectors[e_Front] = {
          Bullet.f_Vectors[e_Front].x - g_ScreenWidth,
          Bullet.f_Vectors[e_Front].y};

      Duplicated->f_Vectors[e_Back] = {
          Bullet.f_Vectors[e_Back].x - g_ScreenWidth,
          Bullet.f_Vectors[e_Back].y};
      break;

    case WhereCollides::Left:
      Duplicated->f_Vectors[e_Front] = {
          g_ScreenWidth + Bullet.f_Vectors[e_Front].x,
          Bullet.f_Vectors[e_Front].y};

      Duplicated->f_Vectors[e_Back] = {
          g_ScreenWidth + Bullet.f_Vectors[e_Back].x,
          Bullet.f_Vectors[e_Back].y};
      break;
  }
}



void Bullet::Update(std::list<BulletType>& Bullets, const float Delta) {
  for (BulletType& Bullet : Bullets) {
    Bullet.f_Vectors[e_Front].x += Bullet.f_Speed * Delta * Bullet.f_Direction.
        x;
    Bullet.f_Vectors[e_Front].y += Bullet.f_Speed * Delta * Bullet.f_Direction.
        y;
    Bullet.f_Vectors[e_Back].x += Bullet.f_Speed * Delta * Bullet.f_Direction.x;
    Bullet.f_Vectors[e_Back].y += Bullet.f_Speed * Delta * Bullet.f_Direction.y;

  }
}



void Bullet::Draw(const std::list<BulletType>& Bullets) {
  constexpr float k_RotCorrection = 90.0F;

  Rectangle Source;
  Rectangle Destination;
  Vector2 Origin;

  for (auto& Bullet : Bullets) {

    Source = {0,
              0,
              static_cast<float>(Bullet.f_Sprite.width),
              static_cast<float>(Bullet.f_Sprite.height)};

    Destination = {
        (Bullet.f_Vectors[e_Front].x + Bullet.f_Vectors[e_Back].x) / 2.0F,
        (Bullet.f_Vectors[e_Front].y + Bullet.f_Vectors[e_Back].y) / 2.0F,
        static_cast<float>(Bullet.f_Sprite.width) * 2.0F,
        static_cast<float>(Bullet.f_Sprite.height) * 2.0F};

    Origin = {static_cast<float>(Bullet.f_Sprite.width),
              static_cast<float>(Bullet.f_Sprite.height)};

    DrawTexturePro(Bullet.f_Sprite, Source, Destination, Origin,
                   k_RotCorrection - Math::GetRotation(Bullet.f_Direction),
                   WHITE);

#ifdef _DEBUG
    DrawCircleV(Bullet.f_Vectors[e_Front], 3, WHITE);
    DrawCircleV(Bullet.f_Vectors[e_Back], 3, WHITE);
#endif

  }

}
