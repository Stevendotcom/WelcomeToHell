#include "Play.h"

#include "Constants.h"
#include "raylib.h"
#include "actors/Player.h"
#include "engine/Collisions.h"
#include "engine/ResManager.h"

using namespace Player;
using namespace Collisions;

namespace {

bool Pause = false;



void Input(PlayerType& Player) {
  Player::Input(Player, Pause);
}



void Update(const float Delta,
            PlayerType& Player,
            PlayerType& Duplicated,
            bool& DuplicatedVisible) {

  auto CollisionPlace = WhereCollides::Down;

  Player::Update(Player, Delta);

  if (IsBorderCircle(Player.f_PositionCenter, Player.f_Radius, CollisionPlace)
      && !DuplicatedVisible) {

    DuplicatedVisible = true;
    Duplicate(Player, Duplicated, CollisionPlace);
  }
  if (DuplicatedVisible) {
    UpdateDuplicate(Player, Duplicated, CollisionPlace, DuplicatedVisible);
  }
}



void PlayDraw(const PlayerType& Player,
              const bool DuplicatedVisible,
              const PlayerType& Duplicated) {
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
    DrawText(TextFormat("Speed= %f", Math::GetMag(Player.f_Speed)), 10, 10, 10,
             WHITE);
    DrawCircleLinesV(Player.f_PositionCenter, Player.f_Radius, RAYWHITE);
    Draw(Player);
    if (DuplicatedVisible) {
      DrawCircleLinesV(Duplicated.f_PositionCenter, Duplicated.f_Radius,
                       RAYWHITE);
      Draw(Duplicated);
    }
  }
  EndDrawing();
}

}



void Play::Play() {

  const Music Music = GetMusic(ResManager::Resources::GameMusic);
  constexpr float k_MusicVol = 0.1F;
  bool Exit = false;
  bool PlayerWon = false;
  static bool DuplicatedVisible = false;
  PlayerType Player;
  PlayerType Duplicated;

  Initialize(Player);

  PlayMusicStream(Music);
  SetMusicVolume(Music, k_MusicVol);

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input(Player);
    Update(GetFrameTime(), Player, Duplicated, DuplicatedVisible);
    UpdateMusicStream(Music);
    PlayDraw(Player, DuplicatedVisible, Duplicated);
  }

}
