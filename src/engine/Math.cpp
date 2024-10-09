#include "Math.h"

#include <cfloat>
#include <cmath>
#include <iostream>

using namespace std;

namespace Math {

using Rads = float;

#pragma region Declarations

/**
 *
 */
float _RadianCast(Rads degree);

#pragma endregion

float GetRotation(const Vector2& a) {
  int quad = 0;
  Rads degree = 0;

  if (a.x > 0) {
    if (a.y < 0) {
      quad = 1;
    } else {
      quad = 4;
    }

  } else {
    if (a.y < 0) {
      quad = 2;
    } else {
      quad = 3;
    }
  }

  switch (quad) {
    case 1:
      degree = atan(-a.y / a.x);
      break;
    case 2:
      degree = PI - atan(-a.y / a.x);
      break;
    case 3:
      degree = PI + atan(-a.y / a.x);
      break;
    case 4:
      degree = 2 * PI - atan(-a.y / a.x);
      break;
    default:
      cout << "Err Math.cpp:54"
           << "\n";
      break;
  }

  return _RadianCast(degree);
}

Vector2 Subtract(const Vector2& a, const Vector2& b) {
  return {(b.x - a.x), (b.y - a.y)};
}

Vector2 Add(const Vector2& a, const Vector2& b) {
  return {(b.x + a.x), (b.y + a.y)};
}

Vector2 Normalize(const Vector2& a, float mag) {
  return {a.x / mag, a.y / mag};
}

float GetMag(const Vector2& a) {
  return sqrtf(powf(a.x, 2) + powf(a.y, 2));
}

bool IsEqual(const Vector2& a, const Vector2& b) {
  return IsEqual(a.x, b.x) && IsEqual(a.y, b.y);
}

bool IsEqual(float a, float b) {
  return a > b - FLT_EPSILON && a < b + FLT_EPSILON;
}

float _RadianCast(Rads degree) {
  return static_cast<Rads>((degree * 180.0f) / PI);
}

} // namespace Math
