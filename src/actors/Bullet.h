#pragma once
#include <list>
#include <raylib.h>

#include "engine/Collisions.h"

namespace Bullet {

struct BulletType {
  Vector2 f_Direction;
  //Front and back
  Vector2 f_Vectors[2];
  float f_Speed;
  Texture2D f_Sprite;
  BulletType *f_Duplicate;
  int f_Id;
};

void Kill(std::list<BulletType>& Bullets, int Id);

void AddToTargets(int Id);

void Execute(std::list<BulletType>& Bullets);

/**
* @brief
*/
void Shoot(std::list<BulletType>& Bullets,
           const Vector2& PlayerDirection,
           float
           PlayerRadius,
           const Vector2& PlayerPosition);

/**
 * @brief
 * @param Bullet
 * @param Duplicated
 * @param CollisionPlace
 * @param BulletDups
 */
void UpdateDuplicate(BulletType& Bullet,
                     BulletType& Duplicated,
                     Collisions::WhereCollides CollisionPlace,
                     std::list<BulletType>& BulletDups);


void Duplicate(BulletType& Bullet,
               BulletType& Duplicated,
               Collisions::WhereCollides CollisionPlace);
/**
 * @brief
 * @param Delta
 */
void Update(std::list<BulletType>& Bullets, float Delta);

/**
 * @brief
 * @param Bullets
 */
void Draw(std::list<BulletType>& Bullets);


};
