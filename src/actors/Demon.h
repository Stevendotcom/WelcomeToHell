#pragma once
#include "raylib.h"
#include <list>

namespace Demon {

struct DemonType {
  Vector2 f_Position;
  Vector2 f_Direction;
  float f_Speed;
  float f_Radius;
  Texture f_Sprite;
  int f_Frame;
  };
    /**
   * @brief
   */
  void Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition);
  /**
   * @brief
   * @param Delta
   */
  void Update(std::list<DemonType>& Demons, float Delta);

  /**
   * @brief
   * @param Demons
   */
  void Draw(const std::list<DemonType>& Demons);

  };
