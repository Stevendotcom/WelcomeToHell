#pragma once
#include <raylib.h>

namespace PowerUps {

using Frame = Rectangle;

enum Powers {

};

struct PowerUp {
  Vector2 f_Position;
  Powers f_Power;
  Texture f_Sprite;
  Frame f_Frame;
  int f_FrameIndex;
  int f_Id;
  bool f_Active;
};

void AddPower(PowerUp& Pow);

void Update(PowerUp& Pow, const Vector2 PlayerPos&);

void Draw(const PowerUp& Pow);

}
