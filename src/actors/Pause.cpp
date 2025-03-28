﻿#include "Pause.h"

#include <string>

#include "raylib.h"

#include "Constants.h"
#include "Player.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

namespace {
bool SoundPlayed = false;
constexpr float k_Scale = 1.5;
constexpr float k_ButtonsSize = 32.0F;
constexpr float k_ButtonsX = 400.0F;
constexpr float k_ButtonsY = 300.0F;
constexpr int k_ScaleBut = 3;
constexpr int k_FontSize = 40;



void PlayHoverSound() {
  const Sound Hover = GetSound(ResManager::Resources::MenuHover);

  if (!IsSoundPlaying(Hover) && !SoundPlayed) {
    PlaySound(Hover);
    SoundPlayed = true;
  }

}



void Input(bool& Exit, bool& Ret) {

  const Vector2 k_MousePos = GetMousePosition();

  constexpr int ReturnTextWidth = 140;
  constexpr int ExitTextWidth = 100;

  if (Math::IsInRect({k_ButtonsX,
                      k_ButtonsY,
                      k_ButtonsSize * k_ScaleBut + ReturnTextWidth,
                      k_ButtonsSize * k_ScaleBut}, k_MousePos)) {

    PlayHoverSound();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      Exit = false;
      Ret = !Exit;
    }

  } else {
    if (Math::IsInRect({k_ButtonsX,
                        k_ButtonsY + k_ButtonsSize * k_ScaleBut,
                        k_ButtonsSize * k_ScaleBut + ExitTextWidth,
                        k_ButtonsSize * k_ScaleBut}, k_MousePos)) {

      PlayHoverSound();

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        Exit = true;
        Ret = !Exit;
      }

    } else {
      SoundPlayed = false;
    }
  }

}



void DrawLocal(const Player::PlayerType& Player) {

  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);
  const Texture2D& k_PauseBG = GetTexture(ResManager::Resources::PauseBG);
  const Texture2D& k_Buttons = GetTexture(ResManager::Resources::Buttons);

  std::string Message;

  int FontSize;

  BeginDrawing();
  {
    ClearBackground(BLACK);

    DrawTexturePro(k_Background, {0,
                                  0,
                                  static_cast<float>(k_Background.width),
                                  static_cast<float>(k_Background.height)}, {0,
                     0,
                     static_cast<float>(g_ScreenWidth),
                     static_cast<float>(g_ScreenHeight)}, {0,
                     0}, 0, WHITE);

    DrawTextureEx(k_PauseBG,
                  {(static_cast<float>(g_ScreenWidth) - static_cast<float>(
                      k_PauseBG.width) * k_Scale) / 2.0F,
                   0}, 0, k_Scale, WHITE);

    DrawTexturePro(k_Buttons, {0,
                               0,
                               k_ButtonsSize,
                               k_ButtonsSize}, {k_ButtonsX,
                                                k_ButtonsY,
                                                k_ButtonsSize * k_ScaleBut,
                                                k_ButtonsSize * k_ScaleBut}, {0,
                     0}, 0, WHITE);

    DrawTexturePro(k_Buttons, {k_ButtonsSize,
                               0,
                               k_ButtonsSize,
                               k_ButtonsSize}, {k_ButtonsX,
                                                k_ButtonsY + k_ButtonsSize *
                                                k_ScaleBut,
                                                k_ButtonsSize * k_ScaleBut,
                                                k_ButtonsSize * k_ScaleBut}, {0,
                     0}, 0, WHITE);

    DrawText(Player.f_Hearts <= 0 ? "Restart" : "Return",
             static_cast<int>(k_ButtonsX + k_ButtonsSize + k_FontSize + 15.0F),
             static_cast<int>(k_ButtonsY + k_ButtonsSize),
             Player.f_Hearts <= 0 ? k_FontSize - 4 : k_FontSize, WHITE);

    DrawText("Return\n\nto Menu",
             static_cast<int>(k_ButtonsX + k_ButtonsSize + k_FontSize + 20.0F),
             static_cast<int>(k_ButtonsY + k_ButtonsSize * k_ScaleBut +
                              k_FontSize - 20), k_FontSize - 4, WHITE);

    if (Player.f_Hearts <= 0) {
      FontSize = 32;
      Message = "You Lost!";
    } else {
      FontSize = 42;
      Message = "Pause";
    }

    DrawText(Message.c_str(),
             (g_ScreenWidth - MeasureText(Message.c_str(), FontSize)) / 2, 228,
             FontSize, WHITE);

  }
  EndDrawing();
}

}



bool Pause::Pause(const Player::PlayerType& Player, bool& CloseWindow) {
  const Sound k_Dropship = GetSound(ResManager::Resources::Dropship);
  bool GotoMenu = false;
  bool Ret = false;
  bool WasPlaying = false;

  ShowCursor();

  if (IsSoundPlaying(k_Dropship)) {
    PauseSound(k_Dropship);
    WasPlaying = true;
  }

  PlaySound(GetSound(ResManager::Resources::MenuOpen));

  while (!GotoMenu && !CloseWindow && !Ret) {
    CloseWindow = WindowShouldClose();
    Input(GotoMenu, Ret);
    DrawLocal(Player);
  }

  if (WasPlaying) {
    ResumeSound(k_Dropship);
  }

  if (!GotoMenu) {
    HideCursor();
  }

  return GotoMenu;
}
