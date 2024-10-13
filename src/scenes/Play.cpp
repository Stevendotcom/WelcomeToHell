#include "Play.h"

#include "Constants.h"
#include "raylib.h"
#include "actors/Player.h"
#include "engine/ResManager.h"

using namespace Player;

namespace {

bool Pause = false;



void Input(PlayerType& Player) {
  Player::Input(Player, Pause);
}



void Update(const float Delta, PlayerType& Player) {
  Player::Update(Player, Delta);
}



void PlayDraw(const PlayerType& Player) {
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
    DrawText(TextFormat("Speed= %f, %f", Player.f_Speed.x, Player.f_Speed.y), 10, 10, 10, WHITE);
    Draw(Player);

  }
  EndDrawing();
}

}



void Play::Play() {

  const Music Music = GetMusic(ResManager::Resources::GameMusic);
  float MusicVol = 0.5F;
  bool Exit = false;
  bool PlayerWon = false;
  PlayerType Player;

  Initialize(Player);

  PlayMusicStream(Music);
  SetMusicVolume(Music, MusicVol);

  while (!Exit && !PlayerWon && !WindowShouldClose()) {
    Input(Player);
    Update(GetFrameTime(), Player);
    UpdateMusicStream(Music);
    PlayDraw(Player);
  }

}
