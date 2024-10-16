#pragma once
#include <raylib.h>

namespace Collisions {
/**
 *
 */
bool IsCircleCircle(const Vector2& APosition, float ARadius, const Vector2& BPosition, float BRadius);
  
bool IsBorderCircle(const Vector2& Position, float Radius, WhereCollides CollisionPlace);

};
