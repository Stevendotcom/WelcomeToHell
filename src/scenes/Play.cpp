#include "Play.h"

#include "Constants.h"
#include "raylib.h"
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



void Input(Player::PlayerType& Player) {
  Player::Input(Player, Pause);
}



void Update(Player::PlayerType& Player,
            Player::PlayerType& Duplicated,
            bool& DuplicatedVisible,
            std::list<Demon::DemonType>& Demons,
            std::list<Demon::DemonType>& DemonDuplicates) {

  auto CollisionPlace = WhereCollides::Down;

  Player::Update(Player, GetFrameTime());

  if (IsBorderCircle(Player.f_PositionCenter, Player.f_Radius, CollisionPlace)
      && !DuplicatedVisible) {

    DuplicatedVisible = true;
    Duplicate(Player, Duplicated, CollisionPlace);
  }
  if (DuplicatedVisible) {
    UpdateDuplicate(Player, Duplicated, CollisionPlace, DuplicatedVisible);
  }

  if (!Demons.empty()) {
    Demon::Update(Demons, GetFrameTime());

    for (auto& Demon : Demons) {

      if (IsBorderCircle(Demon.f_Position, Demon.f_Radius, CollisionPlace) && !
          Demon.f_HasDuplicate) {

        Demon.f_HasDuplicate = true;
        Demon::DemonType Dup;
        Demon::Duplicate(Demon, Dup, CollisionPlace);
        DemonDuplicates.push_back(Dup);
        Demon.f_Duplicate = &DemonDuplicates.back();

      }

      if (Demon.f_HasDuplicate) {
        Demon::UpdateDuplicate(Demon, *Demon.f_Duplicate, CollisionPlace,
                               Demon.f_HasDuplicate, DemonDuplicates);
      }

    }
  }
}



void Draw(const Player::PlayerType& Player,
          const bool DuplicatedVisible,
          const Player::PlayerType& Duplicated,
          std::list<Demon::DemonType>& Demons,
          std::list<Demon::DemonType>& DemonDups) {
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

#ifdef _DEBUG
    DrawText(TextFormat("Speed= %f", Math::GetMag(Player.f_Speed)), 10, 10, 10,
             WHITE);
    DrawCircleLinesV(Player.f_PositionCenter, Player.f_Radius, RAYWHITE);
#endif

    Player::Draw(Player);
    if (DuplicatedVisible) {
      DrawCircleLinesV(Duplicated.f_PositionCenter, Duplicated.f_Radius,
                       RAYWHITE);
      Player::Draw(Duplicated);
    }

    Demon::Draw(Demons);
    if (!DemonDups.empty()) {
      Demon::Draw(DemonDups);
    }
  }
  EndDrawing();
}



void DemonTimer(std::list<Demon::DemonType>& Demons,
                const Vector2& PlayerPosition) {
  Timer += GetFrameTime();
#ifndef _DEBUG
  abort()
  //remove limit
#endif
  if (Timer > TimeLimit && Demons.size() < 3) {
    Timer = 0.0f;
    TimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));
    Demon::Initialize(Demons, PlayerPosition);
  }
}

}



void Play::Play() {

  const Music Music = GetMusic(ResManager::Resources::GameMusic);
  constexpr float k_MusicVol = 0.1F;
  bool Exit = false;
  bool PlayerWon = false;
  static bool DuplicatedVisible = false;
  static bool DemonDuplicatedVisible = false;
  Player::PlayerType Player;
  Player::PlayerType Duplicated;
  std::list<Demon::DemonType> Demons;
  std::list<Demon::DemonType> DuplicatedDemons;

  Player::Initialize(Player);

  PlayMusicStream(Music);
  SetMusicVolume(Music, k_MusicVol);

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input(Player);
    Update(Player, Duplicated, DuplicatedVisible, Demons, DuplicatedDemons);
    DemonTimer(Demons, Player.f_PositionCenter);
    UpdateMusicStream(Music);
    Draw(Player, DuplicatedVisible, Duplicated, Demons, DuplicatedDemons);
  }

}
