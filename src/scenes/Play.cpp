#include "Play.h"

#include "Constants.h"
#include "raylib.h"
#include "actors/Bullet.h"
#include "actors/Demon.h"
#include "actors/Player.h"
#include "engine/Collisions.h"
#include "engine/ResManager.h"

using namespace Collisions;

namespace {

bool Pause = false;
constexpr int k_MaxWaitTime = 5;
float Timer = 0.0f;
float TimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));



void Input(Player::PlayerType& Player, std::list<Bullet::BulletType>& Bullets) {

  if (!Pause) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Accelerate(Player);
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
      Shoot(Bullets, Player.f_Direction, Player.f_Radius,
            Player.f_Position);
    }
  }

}



void ManagePlayerDuplicates(Player::PlayerType& Player,
                            Player::PlayerType& Duplicated,
                            bool& DuplicatedVisible,
                            WhereCollides& CollisionPlace) {
  if (IsBorderCircle(Player.f_Position, Player.f_Radius, CollisionPlace)
      && !DuplicatedVisible) {

    DuplicatedVisible = true;
    Duplicate(Player, Duplicated, CollisionPlace);
  }
  if (DuplicatedVisible) {
    UpdateDuplicate(Player, Duplicated, CollisionPlace, DuplicatedVisible);
  }
}



void ManageDemons(Player::PlayerType& Player,
                 std::list<Demon::DemonType>& Demons,
                 std::list<Demon::DemonType>& DemonDuplicates,
                 std::list<Bullet::BulletType>& Bullets,
                 WhereCollides& CollisionPlace) {

  if (!Demons.empty()) {
    Update(Demons, GetFrameTime());

    for (auto& Demon : Demons) {

      if (IsBorderCircle(Demon.f_Position, Demon.f_Radius, CollisionPlace) && !
          Demon.f_Duplicate) {

        Demon::DemonType Dup;
        Duplicate(Demon, Dup, CollisionPlace);
        DemonDuplicates.push_back(Dup);
        Demon.f_Duplicate = &DemonDuplicates.back();

      }

      if (Demon.f_Duplicate) {
        UpdateDuplicate(Demon, *Demon.f_Duplicate, CollisionPlace,
                        DemonDuplicates);
      }

      if (IsCircleCircle(Player.f_Position, Player.f_Radius,
                         Demon.f_Position, Demon.f_Radius)) {
        Player.f_Hearts--;
        DivideDemon(Demon, Demons);
      }

      if (!Bullets.empty()) {
        for (const auto& Bullet : Bullets) {
          if (IsCircleCircle(Bullet.f_Vectors[0], 1, Demon.f_Position,
                             Demon.f_Radius) || IsCircleCircle(
                  Bullet.f_Vectors[1], 1, Demon.f_Position, Demon.f_Radius)) {
            DivideDemon(Demon, Demons);
            Bullet::AddToTargets(Bullet.f_Id);
          }
        }
      }
      Execute(Bullets);
    }
  }
}



void ManageBullets(std::list<Bullet::BulletType>& Bullets,
                  std::list<Bullet::BulletType>& BulletDuplicates,
                  WhereCollides& CollisionPlace) {
  if (!Bullets.empty()) {
    Update(Bullets, GetFrameTime());

    for (auto& Bullet : Bullets) {

      if (IsDotBorder(Bullet.f_Vectors[0], CollisionPlace)) {

        Bullet::BulletType Dup;
        Duplicate(Bullet, Dup, CollisionPlace);
        BulletDuplicates.push_back(Dup);
        Bullet.f_Duplicate = &BulletDuplicates.back();

      }

      if (Bullet.f_Duplicate) {

        UpdateDuplicate(Bullet, *Bullet.f_Duplicate, CollisionPlace,
                        BulletDuplicates);

      }

    }
  }
}



void Update(Player::PlayerType& Player,
            Player::PlayerType& Duplicated,
            bool& DuplicatedVisible,
            std::list<Demon::DemonType>& Demons,
            std::list<Demon::DemonType>& DemonDuplicates,
            std::list<Bullet::BulletType>& Bullets,
            std::list<Bullet::BulletType>& BulletDuplicates) {


  auto CollisionPlace = WhereCollides::Down;

  Player::Update(Player, GetFrameTime());

  ManagePlayerDuplicates(Player, Duplicated, DuplicatedVisible, CollisionPlace);

  ManageDemons(Player, Demons, DemonDuplicates, Bullets, CollisionPlace);

  ManageBullets(Bullets, BulletDuplicates, CollisionPlace);

  Execute(Demons);
}



void Draw(const Player::PlayerType& Player,
          const bool DuplicatedVisible,
          const Player::PlayerType& Duplicated,
          std::list<Demon::DemonType>& Demons,
          std::list<Demon::DemonType>& DemonDups,
          std::list<Bullet::BulletType>& Bullets,
          std::list<Bullet::BulletType>& BulletDuplicates) {
  const Texture2D& Background = GetTexture(ResManager::Resources::Background);

  BeginDrawing();
  {
    DrawTexturePro(Background,
                   {0,
                    0,
                    static_cast<float>(Background.width),
                    static_cast<float>(Background.height)},
                   {0,
                    0,
                    static_cast<float>(g_ScreenWidth),
                    static_cast<float>(g_ScreenHeight)}, {0, 0}, 0, WHITE);

    {
#ifdef _DEBUG
      DrawText(TextFormat("Speed= %f", Math::GetMag(Player.f_Speed)), 10, 10,
               10, WHITE);
      DrawText(TextFormat("Hearts= %i", Player.f_Hearts), 10, 20, 10, WHITE);
      DrawCircleLinesV(Player.f_Position, Player.f_Radius, RAYWHITE);
#endif

      Player::Draw(Player);
      if (DuplicatedVisible) {

#ifdef _DEBUG
        DrawCircleLinesV(Duplicated.f_Position, Duplicated.f_Radius,
                         RAYWHITE);
#endif

        Player::Draw(Duplicated);
      }
    }

    {
      Demon::Draw(Demons);
      if (!DemonDups.empty()) {
        Demon::Draw(DemonDups, true);
      }
    }

    {
      if (!Bullets.empty()) {
        Bullet::Draw(Bullets);
      }
      if (!BulletDuplicates.empty()) {
        Bullet::Draw(BulletDuplicates);
      }
    }
  }
  EndDrawing();
}



void DemonTimer(std::list<Demon::DemonType>& Demons,
                const Vector2& PlayerPosition) {
  Timer += GetFrameTime();
  if (Timer > TimeLimit) {
    Timer = 0.0f;
    TimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));
    Initialize(Demons, PlayerPosition);
  }
}

}



void Play::Play() {

  const Music Music = GetMusic(ResManager::Resources::GameMusic);
  constexpr float k_MusicVol = 0.1F;
  bool Exit = false;
  bool PlayerWon = false;
  static bool DuplicatedVisible = false;

  Player::PlayerType Player;
  Player::PlayerType Duplicated;
  std::list<Demon::DemonType> Demons;
  std::list<Demon::DemonType> DuplicatedDemons;
  std::list<Bullet::BulletType> Bullets;
  std::list<Bullet::BulletType> BulletDuplicates;

  Initialize(Player);

  PlayMusicStream(Music);
  SetMusicVolume(Music, k_MusicVol);

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input(Player, Bullets);
    Update(Player, Duplicated, DuplicatedVisible, Demons, DuplicatedDemons,
           Bullets, BulletDuplicates);
    DemonTimer(Demons, Player.f_Position);
    UpdateMusicStream(Music);
    Draw(Player, DuplicatedVisible, Duplicated, Demons, DuplicatedDemons,
         Bullets, BulletDuplicates);
  }

}
