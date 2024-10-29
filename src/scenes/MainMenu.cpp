#include "MainMenu.h"

#include <array>
#include <iostream>
#include <raylib.h>

#include "Constants.h"
#include "engine/Error.h"
#include "engine/Math.h"
#include "engine/ResManager.h"
#include "engine/SceneManager.h"

namespace {

struct Btn {
  Rectangle f_Dest;
  bool f_IsHover;
  bool f_HasSoundPlayed;
  std::string f_Text;
};



constexpr Rectangle k_BackgroundButtonSource = {0, 0, 58.0F, 25.0F};
constexpr Rectangle k_ButtonDef = {0, 0, 250.0F, 50.0F};

constexpr float k_MiddleScreenWidth = g_ScreenWidth / 2.0F;
constexpr float k_BMargin = 50.0F;
constexpr float k_BPad = 20.0F;

constexpr int k_BtnAmount = 3;
constexpr int k_FontSize = 36;

const std::string k_Title = "Welcome To Hell";

std::array<Btn, k_BtnAmount> Btns;
auto SceneChange = SceneManager::Scenes::Exit;



void InitBtns() {
  int I = 0;
  for (auto& Btn : Btns) {
    I++;
    Btn.f_Dest = k_ButtonDef;
    Btn.f_Dest.x = k_MiddleScreenWidth - (k_ButtonDef.width / 2.0F);
    //Note the reverse order
    Btn.f_Dest.y = g_ScreenHeight - k_BMargin - (k_BPad + Btn.f_Dest.height) *
                   static_cast<float>(I);

    switch (I) {
      case 1:
        Btn.f_Text = "Exit";
        break;
      case 2:
        Btn.f_Text = "Credits";
        break;
      case 3:
        Btn.f_Text = "Play";
        break;
      default:
        Error::Unhandled(__LINE__, __FILE__);
    }
  }
}



bool Input() {

  const Vector2 MousePos = GetMousePosition();

  int I = 0;
  for (auto& Btn : Btns) {

    I++;
    if (Math::IsInRect(Btn.f_Dest, MousePos)) {

      Btn.f_IsHover = true;

      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

        switch (I) {
          case 1:
            SceneChange = SceneManager::Scenes::Exit;
            break;
          case 2:
            SceneChange = SceneManager::Scenes::Credits;
            break;
          case 3:
            SceneChange = SceneManager::Scenes::Play;
            break;
          default:
            Error::Unhandled(__LINE__, __FILE__);
        }
        return true;

      }

    } else {
      Btn.f_IsHover = false;
      Btn.f_HasSoundPlayed = false;
    }

  }
  return false;
}



void Draw() {
  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);
  const Texture2D& k_Btn = GetTexture(ResManager::Resources::Btn);
  const Texture2D& k_BtnPressed = GetTexture(ResManager::Resources::BtnPressed);
  const Sound& k_Hover = GetSound(ResManager::Resources::MenuHover);
  constexpr int k_TitleFontSize = 64;
  constexpr int k_TMargin = 20;

  BeginDrawing();

  ClearBackground(BLACK);
  DrawTexturePro(k_Background,
                 {0,
                  0,
                  static_cast<float>(k_Background.width),
                  static_cast<float>(k_Background.height)},
                 {0,
                  0,
                  static_cast<float>(g_ScreenWidth),
                  static_cast<float>(g_ScreenHeight)}, {0, 0}, 0, WHITE);
  DrawText(k_Title.c_str(),
           (g_ScreenWidth - MeasureText(k_Title.c_str(), k_TitleFontSize)) / 2,
           k_TMargin + k_TitleFontSize, k_TitleFontSize, WHITE);

  for (auto& Btn : Btns) {

    DrawTexturePro((Btn.f_IsHover ? k_BtnPressed : k_Btn),
                   k_BackgroundButtonSource, Btn.f_Dest, {0, 0}, 0, WHITE);

    DrawText(Btn.f_Text.c_str(),
             static_cast<int>(Btn.f_Dest.x + (
                                Btn.f_Dest.width - static_cast<float>(
                                  MeasureText(Btn.f_Text.c_str(), k_FontSize)))
                              / 2.0F),
             static_cast<int>(Btn.f_Dest.y + (Btn.f_Dest.height - k_FontSize) /
                              2), k_FontSize, WHITE);

    if (Btn.f_IsHover && !IsSoundPlaying(k_Hover) && !Btn.f_HasSoundPlayed) {
      PlaySound(k_Hover);
      Btn.f_HasSoundPlayed = true;
    }

  }

  EndDrawing();

}

}



void MainMenu::Menu() {
  const Music k_MenuMusic = GetMusic(ResManager::Resources::MainMenuMusic);

  PlayMusicStream(k_MenuMusic);
  SetMusicVolume(k_MenuMusic, 1);
  InitBtns();

  while (!WindowShouldClose() && !Input()) {
    UpdateMusicStream(k_MenuMusic);
    Draw();
  }

  StopMusicStream(k_MenuMusic);
  ChangeScene(SceneChange);
}
