#include "Animations.h"

namespace {

using namespace Animations;



Frame GetNextFrame(const Vector2& SpriteSize,
                   int& FrameIndex,
                   const int Cols,
                   const int Rows) {

  const Frame NewFrame = {
      (static_cast<float>(FrameIndex % Cols) * (
         SpriteSize.x / static_cast<float>(Cols))),
      (FrameIndex > 6 ? SpriteSize.y / static_cast<float>(Rows) : 0),
      (SpriteSize.x / static_cast<float>(Cols)),
      (SpriteSize.y / static_cast<float>(Rows)),};

  FrameIndex++;
  return NewFrame;
}

}


bool Animations::Update(Frame& Frame,
                        const int Rows,
                        const int Cols,
                        int& FrameIndex,
                        float& FrameTime,
                        const float Delta,
                        const Vector2& SpriteSize) {

  constexpr float k_Minute = 60.0F;
  bool HasUpdated = false;
  if (FrameTime > static_cast<float>(Cols * Rows) / k_Minute) {
    Frame = GetNextFrame(SpriteSize, FrameIndex, Cols, Rows);
    FrameTime = 0;
    HasUpdated = true;
  }

  FrameTime += Delta;
  return HasUpdated;
}
