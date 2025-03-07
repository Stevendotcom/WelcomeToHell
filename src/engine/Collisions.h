#pragma once
#include "raylib.h"

namespace Collisions {

enum class WhereCollides {
  Up,
  Down,
  Left,
  Right
};



/**
 *
 */
bool IsCircleCircle(const Vector2& APosition,
                    float ARadius,
                    const Vector2& BPosition,
                    float BRadius);

bool IsBorderCircle(const Vector2& Position,
                    float Radius,
                    WhereCollides& CollisionPlace);

bool IsDotBorder(const Vector2& Position, WhereCollides& CollisionPlace);

bool IsCircleSquare(const Vector2& CirclePosition,
                    float Radius,
                    const Vector2& SquarePosition,
                    const Vector2& Size);
};
