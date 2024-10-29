#pragma once
#include "engine/Math.h"
#include "engine/Collisions.h"

namespace Player {

struct PlayerType {
  float f_Acceleration;
  float f_Radius;
  int f_Hearts;
  int f_Score;
  Vector2 f_Position;
  Vector2 f_Speed;
  Vector2 f_Direction;
  Texture f_Sprite;
  bool f_IsInvencible;
};



/**
 * @brief
 * @param Player
 */
void Initialize(PlayerType& Player);

/**
 * @brief
 * @param Player
 */
void Accelerate(PlayerType& Player);

/**
 * 
 * @param Player 
 * @param Duplicated 
 * @param CollisionPlace 
 */
void Duplicate(const PlayerType& Player, PlayerType& Duplicated, Collisions::WhereCollides CollisionPlace);

/**
 * 
 * @param Player 
 * @param Duplicated 
 * @param CollisionPlace 
 * @param DuplicatedVisible 
 */
void UpdateDuplicate(PlayerType& Player,
                     PlayerType& Duplicated,
                     Collisions::WhereCollides CollisionPlace,
                     bool& DuplicatedVisible);

/**
 * @brief
 * @param Player
 * @param Delta
 * @param IsDuplicated
 */
void Update(PlayerType& Player, float Delta, bool IsDuplicated = false);

/**
 * @brief
 * @param Player
 */
void Draw(const PlayerType& Player);
};
