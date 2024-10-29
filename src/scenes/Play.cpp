#include "Play.h"

#include <iostream>
#include <ostream>

#include "Constants.h"
#include "raylib.h"
#include "actors/Bullet.h"
#include "actors/Demon.h"
#include "actors/Player.h"
#include "engine/Collisions.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

using namespace Collisions;

namespace {

constexpr int k_MaxWaitTime = 5;
constexpr int k_RMargin = 30;
constexpr int k_ScalePause = 2;
int k_ScoreGain = 234;
bool Pause = false;
float Timer = 0.0f;
float TimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));
constexpr float k_TMargin = 30.0F;
constexpr float k_LMargin = 20.0F;
constexpr float k_HeartSpriteSize = 16.0F;

constexpr Rectangle k_SourcePause = {64.0F, 0, 32.0F, 32.0F};
constexpr Rectangle k_DestPause{
    g_ScreenWidth - (k_RMargin + k_SourcePause.width * k_ScalePause),
    k_TMargin,
    k_SourcePause.width * k_ScalePause,
    k_SourcePause.height * k_ScalePause};



void Input(Player::PlayerType& Player, std::list<Bullet::BulletType>& Bullets) {

  if (!Pause) {
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
      Accelerate(Player);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      Shoot(Bullets, Player.f_Direction, Player.f_Radius, Player.f_Position);
    }
  }

}



void ManagePlayerDuplicates(Player::PlayerType& Player,
                            Player::PlayerType& Duplicated,
                            bool& DuplicatedVisible,
                            WhereCollides& CollisionPlace) {
  if (IsBorderCircle(Player.f_Position, Player.f_Radius, CollisionPlace) && !
      DuplicatedVisible) {

    DuplicatedVisible = true;
    Duplicate(Player, Duplicated, CollisionPlace);
  }
  if (DuplicatedVisible) {
    UpdateDuplicate(Player, Duplicated, CollisionPlace, DuplicatedVisible);
  }
}



void ManageDemons(Player::PlayerType& Player,
                  std::list<Demon::DemonType>& Demons,
                  std::list<Bullet::BulletType>& Bullets,
                  WhereCollides& CollisionPlace) {

  if (!Demons.empty()) {
    Update(Demons, GetFrameTime());

    for (auto& Demon : Demons) {

      if (IsBorderCircle(Demon.f_Position, Demon.f_Radius, CollisionPlace) && !
          Demon.f_Duplicate) {

        auto* Duplicated = new Demon::DemonType();
        Duplicate(Demon, Duplicated, CollisionPlace);
        Demon.f_Duplicate = Duplicated;
      }

      if (Demon.f_Duplicate) {
        UpdateDuplicate(Demon, Demon.f_Duplicate, CollisionPlace);
      }

      if (IsCircleCircle(Player.f_Position, Player.f_Radius, Demon.f_Position,
                         Demon.f_Radius)) {
        Player.f_Hearts--;
        DivideDemon(Demon, Demons);
      }

      if (!Bullets.empty()) {
        for (const auto& Bullet : Bullets) {
          if (IsCircleCircle(Bullet.f_Vectors[0], 1, Demon.f_Position,
                             Demon.f_Radius) || IsCircleCircle(
                  Bullet.f_Vectors[1], 1, Demon.f_Position, Demon.f_Radius)) {
            Player.f_Score += k_ScoreGain;
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
            std::list<Bullet::BulletType>& Bullets,
            std::list<Bullet::BulletType>& BulletDuplicates) {

  auto CollisionPlace = WhereCollides::Down;

  Player::Update(Player, GetFrameTime());

  ManagePlayerDuplicates(Player, Duplicated, DuplicatedVisible, CollisionPlace);

  ManageDemons(Player, Demons, Bullets, CollisionPlace);

  ManageBullets(Bullets, BulletDuplicates, CollisionPlace);

  Execute(Demons);
}



void DrawLives(const Player::PlayerType& Player) {
  constexpr float k_LPadding = 45.0F;
  constexpr float k_Scale = 3.0F;

  Vector2 Position;

  for (int I = 0; I < Player.f_Hearts; I++) {
    Position = {
        k_LMargin + (k_LPadding + k_HeartSpriteSize) * static_cast<float>(I),
        k_TMargin};
    DrawTextureEx(GetTexture(ResManager::Resources::HeartBackground), Position,
                  0, k_Scale, WHITE);
    DrawTextureEx(GetTexture(ResManager::Resources::HeartSprite), Position, 0,
                  k_Scale, WHITE);
  }
}



void DrawUI(const Player::PlayerType& Player) {
  constexpr int k_FontSize = 30;

  DrawLives(Player);

  DrawTexturePro(GetTexture(ResManager::Resources::Pause), k_SourcePause, k_DestPause,
                 {0, 0}, 0, WHITE);

  DrawText(TextFormat("Score: %i", Player.f_Score),
           static_cast<int>(k_LMargin) + k_FontSize,
           static_cast<int>(k_TMargin) + static_cast<int>(k_HeartSpriteSize) * 3
           + 10, k_FontSize, WHITE);
}



void Draw(const Player::PlayerType& Player,
          const bool DuplicatedVisible,
          const Player::PlayerType& Duplicated,
          std::list<Demon::DemonType>& Demons,
          const std::list<Bullet::BulletType>& Bullets,
          const std::list<Bullet::BulletType>& BulletDuplicates) {
  const Texture2D& Background = GetTexture(ResManager::Resources::Background);

  BeginDrawing();
  {
    ClearBackground(BLACK);
    DrawTexturePro(Background,
                   {0,
                    0,
                    static_cast<float>(Background.width),
                    static_cast<float>(Background.height)},
                   {0,
                    0,
                    static_cast<float>(g_ScreenWidth),
                    static_cast<float>(g_ScreenHeight)}, {0, 0}, 0, WHITE);

    Player::Draw(Player);
    if (DuplicatedVisible) {

#ifdef _DEBUG
      DrawCircleLinesV(Duplicated.f_Position, Duplicated.f_Radius, RAYWHITE);
#endif

      Player::Draw(Duplicated);
    }

    for (auto& Demon : Demons) {
      Demon::Draw(Demon);
      if (Demon.f_Duplicate) {
        Demon::Draw(*Demon.f_Duplicate, true);
      }
    }

    if (!Bullets.empty()) {
      Bullet::Draw(Bullets);
    }

    if (!BulletDuplicates.empty()) {
      Bullet::Draw(BulletDuplicates);
    }

    DrawUI(Player);

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



bool HasPlayerLost(const Player::PlayerType& Player) {
  return Player.f_Hearts <= 0;
}

}



void Play::Play() {

  const Music Music = GetMusic(ResManager::Resources::GameMusic);
  constexpr float k_MusicVol = 0.1F;
  bool Exit = false;
  static bool DuplicatedVisible = false;

  Player::PlayerType Player;
  Player::PlayerType Duplicated;
  std::list<Demon::DemonType> Demons;
  std::list<Bullet::BulletType> Bullets;
  std::list<Bullet::BulletType> BulletDuplicates;

  Initialize(Player);

  PlayMusicStream(Music);
  SetMusicVolume(Music, k_MusicVol);

  while (!Exit && !WindowShouldClose()) {
    Input(Player, Bullets);
    Update(Player, Duplicated, DuplicatedVisible, Demons, Bullets,
           BulletDuplicates);
    Exit = HasPlayerLost(Player);
    DemonTimer(Demons, Player.f_Position);
    UpdateMusicStream(Music);
    Draw(Player, DuplicatedVisible, Duplicated, Demons, Bullets,
         BulletDuplicates);
  }

  ChangeScene(SceneManager::Scenes::Exit); //TODO CHANGE
}
