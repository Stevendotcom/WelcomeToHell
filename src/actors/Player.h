#pragma once
#include "engine/Math.h"

namespace Player {

struct PlayerType {
  float f_Acceleration;
  float f_Radius;
  int f_Hearts;
  Vector2 f_PositionCenter;
  Vector2 f_Speed;
  Vector2 f_Direction;
  Texture f_Sprite;

};



/**
 * @brief
 * @param Player
 */
void Initialize(PlayerType& Player);

/**
 * @brief
 * @param Player
 * @param MousePosition
 */
void Accelerate(PlayerType& Player, const Vector2& MousePosition);

/**
 * @brief
 * @param Player
 * @param Pause
 */
void Input(PlayerType& Player, float Pause);

/**
 * @brief
 * @param Player
 * @param Delta
 */
void Update(PlayerType& Player, float Delta);

/**
 * @brief
 * @param Player
 */
void Draw(const PlayerType& Player);
};
