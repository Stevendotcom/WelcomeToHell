#include "Pause.h"

#include "Constants.h"
#include "engine/Math.h"
#include "engine/ResManager.h"

namespace {
constexpr float k_Scale = 1.5;
constexpr float k_ButtonsSize = 32.0F;
constexpr float k_ButtonsX = 400.0F;
constexpr float k_ButtonsY = 300.0F;
constexpr int k_ScaleBut = 3;
constexpr int k_FontSize = 40;

void Input(bool& Exit, bool& Ret) {
  const Vector2 k_MousePos = GetMousePosition();
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    //Ret
    if (Math::IsInRect({k_ButtonsX,
                    k_ButtonsY,
                    k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut}, k_MousePos)) {
      Exit = false;
      Ret = !Exit;
    }
    //exit
    else if (Math::IsInRect({k_ButtonsX,
                    k_ButtonsY + k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut}, k_MousePos)) {
      Exit = true;
      Ret = !Exit;
    }
  }
}



void Draw() {

  const Texture2D& k_Background = GetTexture(ResManager::Resources::Background);
  const Texture2D& k_PauseBG = GetTexture(ResManager::Resources::PauseBG);
  const Texture2D& k_Buttons = GetTexture(ResManager::Resources::Buttons);

  BeginDrawing();
  {
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

    DrawTextureEx(k_PauseBG,
                  {(static_cast<float>(g_ScreenWidth) - static_cast<float>(
                      k_PauseBG.width) * k_Scale) / 2.0F,
                   0}, 0, k_Scale, WHITE);

    DrawTexturePro(k_Buttons, {0, 0, k_ButtonsSize, k_ButtonsSize},
                   {k_ButtonsX,
                    k_ButtonsY,
                    k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut}, {0, 0}, 0, WHITE);

    DrawTexturePro(k_Buttons, {k_ButtonsSize, 0, k_ButtonsSize, k_ButtonsSize},
                   {k_ButtonsX,
                    k_ButtonsY + k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut,
                    k_ButtonsSize * k_ScaleBut}, {0, 0}, 0, WHITE);

    DrawText("Return",
             static_cast<int>(k_ButtonsX + k_ButtonsSize + k_FontSize + 15.0F),
             static_cast<int>(k_ButtonsY + k_ButtonsSize), k_FontSize, WHITE);
    DrawText(
        "Exit",
        static_cast<int>(k_ButtonsX + k_ButtonsSize + k_FontSize + 25.0F),
        static_cast<int>(k_ButtonsY + k_ButtonsSize * k_ScaleBut + k_FontSize),
        k_FontSize, WHITE);
  }
  EndDrawing();
}

}



bool Pause::Pause() {
  bool Exit = false;
  bool Ret = false;
  while (!Exit && !WindowShouldClose() && !Ret) {
    Input(Exit, Ret);
    Draw();
  }

  return Exit || WindowShouldClose();
}
