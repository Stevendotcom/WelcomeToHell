#pragma once
#include <list>

#include "raylib.h"
#include "engine/Collisions.h"

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
  int f_Id;
  DemonType* f_Duplicate;
};



void ChangeDirection(DemonType& Demon);

void DivideDemon(DemonType& Demon, std::list<DemonType>& Demons);

/**
* @brief
*/
void Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition);

/**
 * @brief
 * @param Demon
 * @param Duplicated
 * @param CollisionPlace
 */
void UpdateDuplicate(DemonType& Demon,
                     DemonType& Duplicated,
                     Collisions::WhereCollides CollisionPlace);

void Duplicate(const DemonType& Demon,
               DemonType* Duplicated,
               Collisions::WhereCollides CollisionPlace);

void Execute(std::list<DemonType>& Demons);

/**
 * @brief
 * @param Delta
 */
void Update(std::list<DemonType>& Demons, float Delta);

/**
 * @brief
 * @param Demon
 * @param IsDup
 */
void Draw(DemonType& Demon, bool IsDup = false);

};
