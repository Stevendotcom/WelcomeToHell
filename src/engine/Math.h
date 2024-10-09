#include "raylib.h"


namespace Math {

/**
 *
 */
float GetRotation(const Vector2& a);

/**
 * 
 */
Vector2 Subtract(const Vector2& a, const Vector2& b);
/**
  *
  */
Vector2 Add(const Vector2& a, const Vector2& b);

/**
  *
  */
Vector2 Normalize(const Vector2& a, float mag);

/**
  *
  */
float GetMag(const Vector2& a);

/**
 *
 */
bool IsEqual(const Vector2& a, const Vector2& b);

/**
 *
 */
bool IsEqual(float a, float b);

} // namespace Math
