#pragma once
#include "raylib.h"

namespace Math {

/**
 *
 */
float GetRotation(const Vector2& A);

/**
 * 
 */
Vector2 Subtract(const Vector2& A, const Vector2& B);

/**
  *
  */
Vector2 Add(const Vector2& A, const Vector2& B);

/**
  *
  */
Vector2 Normalize(const Vector2& A, float Mag);

/**
  *
  */
float GetMag(const Vector2& A);

/**
 *
 */
bool IsEqual(const Vector2& A, const Vector2& B);

/**
 *
 */
bool IsEqual(float A, float B);

} // namespace Math
