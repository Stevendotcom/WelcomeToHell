#pragma once
#include "raylib.h"
#include <list>

namespace Demon {

using Frame = Rectangle;

struct DemonType {
  Vector2 f_Position;
  Vector2 f_Direction;
  float f_Speed;
  float f_Radius;
  Texture f_Sprite;
  Frame f_Frame;
  int f_FrameIndex;
  };
    /**
   * @brief
   */
  void Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition);
  /**
   * @brief
   * @param PlayerPosition
   * @param Delta
   */
  void Update(std::list<DemonType>& Demons, const Vector2& PlayerPosition, float Delta);

  /**
   * @brief
   * @param Demons
   */
  void Draw(std::list<DemonType>& Demons);

  };
