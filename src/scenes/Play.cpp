#include "Play.h"

#include <list>

#include "raylib.h"

#include "Constants.h"
#include "actors/Beholder.h"
#include "actors/Bullet.h"
#include "actors/Demon.h"
#include "actors/Pause.h"
#include "actors/Player.h"
#include "actors/PowerUps.h"
#include "engine/Collisions.h"
#include "engine/Math.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

using namespace Collisions;

namespace {

constexpr int k_MaxWaitTime = 5;
constexpr int k_RMargin = 30;
constexpr int k_ScalePause = 2;
constexpr int k_ScoreGain = 234;

constexpr float k_InvencibleTimerDuration = 3.0F;
constexpr float k_TMargin = 30.0F;
constexpr float k_LMargin = 20.0F;
constexpr float k_HeartSpriteSize = 16.0F;
constexpr float k_BoostTime = 2.5f;

bool Pause = false;
bool Exit = false;

float DemonSpawnTimer = 0.0F;
float DemonSpawnerTimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));
float InvencibleTimer = 0.0F;
float BoostTimer = 0.0F;
float NewPowerTimer = 0.0F;
float NewPowerIn = static_cast<float>(GetRandomValue(1, 3));
float NewBeholderTimer = 0.0F;
float NewBeholderIn = static_cast<float>(GetRandomValue(15, 20));

constexpr Rectangle k_SourcePause = {64.0F,
                                     0,
                                     32.0F,
                                     32.0F};
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
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

      if (Math::IsInRect(k_DestPause, GetMousePosition())) {
        Exit = Pause::Pause(Player);
      } else {
        Shoot(Bullets, Player.f_Direction, Player.f_Radius, Player.f_Position);
      }
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

      if (!Player.f_IsInvencible && IsCircleCircle(
              Player.f_Position, Player.f_Radius, Demon.f_Position,
              Demon.f_Radius)) {
        Player.f_Hearts--;
        DivideDemon(Demon, Demons);
        Player.f_IsInvencible = true;
      }

      if (!Bullets.empty()) {
        for (const auto& Bullet : Bullets) {
          if (IsCircleCircle(Bullet.f_Vectors[0], 1, Demon.f_Position,
                             Demon.f_Radius) || IsCircleCircle(
                  Bullet.f_Vectors[1], 1, Demon.f_Position, Demon.f_Radius)) {
            Player.f_Score += k_ScoreGain;
            PlaySound(GetSound(ResManager::Resources::Hit));
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
                   WhereCollides& CollisionPlace) {
  if (!Bullets.empty()) {
    Update(Bullets, GetFrameTime());

    for (auto& Bullet : Bullets) {

      if (IsDotBorder(Bullet.f_Vectors[0], CollisionPlace)) {

        auto* Dup = new Bullet::BulletType();
        Duplicate(Bullet, Dup, CollisionPlace);
        Bullet.f_Duplicate = Dup;

      }

      if (Bullet.f_Duplicate) {

        UpdateDuplicate(Bullet, Bullet.f_Duplicate, CollisionPlace);

      }

    }
  }
}



void Update(Player::PlayerType& Player,
            Player::PlayerType& Duplicated,
            bool& DuplicatedVisible,
            std::list<Demon::DemonType>& Demons,
            std::list<Bullet::BulletType>& Bullets,
            std::list<PowerUps::PowerUp>& Powers,
            std::list<Beholder::BeholderType>& Beholders) {

  auto CollisionPlace = WhereCollides::Down;

  const float Delta = GetFrameTime();

  if (Player.f_IsInvencible) {
    InvencibleTimer += Delta;
    if (InvencibleTimer >= k_InvencibleTimerDuration) {
      InvencibleTimer = 0;
      Player.f_IsInvencible = false;
    }
  }

  if (Player.f_IsPowerBoostActive) {
    BoostTimer += Delta;
    if (BoostTimer >= k_BoostTime) {
      BoostTimer = 0;
      Player.f_IsPowerBoostActive = false;
      Player.f_Acceleration = Player.f_DefAccel;
    }
  }

  NewPowerTimer += Delta;
  if (NewPowerTimer >= NewPowerIn) {
    NewPowerTimer = 0;
    NewPowerIn = static_cast<float>(GetRandomValue(3, 6));
    AddPower(Powers);
  }

  Player::Update(Player, Delta);

  PowerUps::Update(Powers, Player, Delta);

  Beholder::Update(Beholders, Player, Delta);

  ManagePlayerDuplicates(Player, Duplicated, DuplicatedVisible, CollisionPlace);

  ManageDemons(Player, Demons, Bullets, CollisionPlace);

  ManageBullets(Bullets, CollisionPlace);

  Execute(Demons);

  Execute(Powers);

  Execute(Beholders);
}



void DemonTimer(std::list<Demon::DemonType>& Demons,
                const Vector2& PlayerPosition) {
  Timer += GetFrameTime();
  if (Timer > TimeLimit) {
    Timer = 0.0F;
    TimeLimit = static_cast<float>(GetRandomValue(0, k_MaxWaitTime));
    Initialize(Demons, PlayerPosition);
  }
}



bool HasPlayerLost(const Player::PlayerType& Player) {
  if (Player.f_Hearts <= 0) {
    Exit = Pause::Pause(Player);
    if (!Exit) {
      return true;
    }
  }
  return false;
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

  DrawTexturePro(GetTexture(ResManager::Resources::Buttons), k_SourcePause,
                 k_DestPause, {0,
                               0}, 0, WHITE);

  DrawText(TextFormat("Score: %i", Player.f_Score),
           static_cast<int>(k_LMargin) + k_FontSize,
           static_cast<int>(k_TMargin) + static_cast<int>(k_HeartSpriteSize) * 3
           + 10, k_FontSize, WHITE);
}



void Draw(const Player::PlayerType& Player,
          const bool DuplicatedVisible,
          const Player::PlayerType& Duplicated,
          const std::list<Demon::DemonType>& Demons,
          const std::list<Bullet::BulletType>& Bullets,
          const std::list<PowerUps::PowerUp>& Powers,
          const std::list<Beholder::BeholderType>& Beholders) {

  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);

  BeginDrawing();
  {
    ClearBackground(BLACK);

    //Background
    DrawTexturePro(k_Background, {0,
                                  0,
                                  static_cast<float>(k_Background.width),
                                  static_cast<float>(k_Background.height)}, {0,
                     0,
                     static_cast<float>(g_ScreenWidth),
                     static_cast<float>(g_ScreenHeight)}, {0,
                     0}, 0, WHITE);

    //Powers
    for (const auto& Power : Powers) {
      PowerUps::Draw(Power);
    }

    //Player
    Player::Draw(Player);

    if (DuplicatedVisible) {
      Player::Draw(Duplicated);
    }

    //Demons
    for (const auto& Demon : Demons) {
      Demon::Draw(Demon);
      if (Demon.f_Duplicate) {
        Demon::Draw(*Demon.f_Duplicate);
      }
    }

    //Bullets
    for (const auto& Bullet : Bullets) {
      Bullet::Draw(Bullet);
      if (Bullet.f_Duplicate) {
        Bullet::Draw(*Bullet.f_Duplicate);
      }
    }

    //Beholder
    for (const auto& Beholder: Beholders){
      Beholder::Draw(Beholder);
    }

    DrawUI(Player);

  }
  EndDrawing();
}


}



void Play::Play() {

  using namespace std;

  const Music k_Music = GetMusic(ResManager::Resources::GameMusic);
  const Sound k_Dropship = GetSound(ResManager::Resources::Dropship);
  constexpr float k_MusicVol = 0.5F;
  bool DuplicatedVisible = false;
  bool Restart = false;

  Player::PlayerType Player;
  Player::PlayerType Duplicated;
  list<Demon::DemonType> Demons;
  list<Bullet::BulletType> Bullets;
  list<PowerUps::PowerUp> Powers;
  list<Beholder::BeholderType> Beholders;

  Initialize(Player);

  PlayMusicStream(k_Music);
  SetMusicVolume(k_Music, k_MusicVol);
  PlaySound(k_Dropship);
  SetSoundVolume(k_Dropship, 0.1F);

  while (!Exit && !WindowShouldClose()) {
    if (!IsSoundPlaying(k_Dropship)) {
      PlaySound(k_Dropship);
    }
    if (Restart) {
      Initialize(Player);
      Clear(Demons);
      Clear(Bullets);
      Clear(Beholders);
      Powers.clear();
    }
    Input(Player, Bullets);
    Update(Player, Duplicated, DuplicatedVisible, Demons, Bullets, Powers,
           Beholders);
    Restart = HasPlayerLost(Player);
    DemonTimer(Demons, Player.f_Position);
    UpdateMusicStream(k_Music);
    Draw(Player, DuplicatedVisible, Duplicated, Demons, Bullets, Powers, Beholders);

  }

  //they have duplicates, so this needs to be called after
  Clear(Demons);
  Clear(Bullets);

  StopMusicStream(k_Music);
  StopSound(k_Dropship);
  ChangeScene(SceneManager::Scenes::Exit);
}
