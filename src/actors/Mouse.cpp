#include "Mouse.h"

#include "engine/ResManager.h"


bool Mouse::IsAccelerating() {
  return IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}


bool Mouse::IsFiring() {
  return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}


void Mouse::Initialize(MouseType& Mouse) {
  Mouse = {GetMousePosition(),
           GetTexture(ResManager::Resources::Mouse),
           35};
}


void Mouse::Update(MouseType& Mouse) {
  Mouse.f_Position = GetMousePosition();
}


void Mouse::Draw(const MouseType& Mouse) {

  const Rectangle Source = {
      IsAccelerating() ? 0 : static_cast<float>(Mouse.f_Sprite.width) / 2.0f,
      0,
      static_cast<float>(Mouse.f_Sprite.width) / 2.0f,
      static_cast<float>(Mouse.f_Sprite.height)};

  const Rectangle Dest = {Mouse.f_Position.x,
                          Mouse.f_Position.y,
                          Mouse.f_Radius * 2.0F,
                          Mouse.f_Radius * 2.0F};

  DrawTexturePro(Mouse.f_Sprite, Source, Dest, {Mouse.f_Radius,
                                                Mouse.f_Radius}, 0, WHITE);
}
