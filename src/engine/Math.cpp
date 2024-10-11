#include "Math.h"

#include <cfloat>
#include <cmath>
#include <iostream>

using namespace std;

namespace {

using Rads = float;



float RadianCast(const Rads Degree) {
  return Degree * 180.0F / PI;
}

}



float Math::GetRotation(const Vector2& A) {
  int Quad = 0;
  Rads Degree = 0;

  if (A.x > 0) {
    if (A.y < 0) {
      Quad = 1;
    } else {
      Quad = 4;
    }

  } else {
    if (A.y < 0) {
      Quad = 2;
    } else {
      Quad = 3;
    }
  }

  switch (Quad) {
    case 1:
      Degree = atan(-A.y / A.x);
      break;
    case 2:
      Degree = PI - atan(-A.y / A.x);
      break;
    case 3:
      Degree = PI + atan(-A.y / A.x);
      break;
    case 4:
      Degree = 2 * PI - atan(-A.y / A.x);
      break;
    default:
      cerr << "Err Math.cpp:54" << "\n";
      break;
  }

  return RadianCast(Degree);
}



Vector2 Math::Subtract(const Vector2& A, const Vector2& B) {
  return {(B.x - A.x), (B.y - A.y)};
}



Vector2 Math::Add(const Vector2& A, const Vector2& B) {
  return {(B.x + A.x), (B.y + A.y)};
}



Vector2 Math::Normalize(const Vector2& A, const float Mag) {
  return {A.x / Mag, A.y / Mag};
}



float Math::GetMag(const Vector2& A) {
  return sqrtf(powf(A.x, 2) + powf(A.y, 2));
}



bool Math::IsEqual(const Vector2& A, const Vector2& B) {
  return IsEqual(A.x, B.x) && IsEqual(A.y, B.y);
}



bool IsEqual(const float A, const float B) {
  return A > B - FLT_EPSILON && A < B + FLT_EPSILON;
}
