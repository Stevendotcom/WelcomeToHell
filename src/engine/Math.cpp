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

  if (A.x >= 0) {
    if (A.y <= 0) {
      Quad = 1;
    } else {
      Quad = 4;
    }

  } else {
    if (A.y <= 0) {
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
      __fallthrough case 3:
      Degree = PI + atan(-A.y / A.x);
      break;
    case 4:
      Degree = 2 * PI + atan(-A.y / A.x);
      break;
    default:
      cerr << "Err Math.cpp:54" << "\n";
      break;
  }

  return RadianCast(Degree);
}



Vector2 Math::Rotate(const Vector2& A, const float Angle) {
  //Angle sum and difference identities
  const float Alpha = tan(Angle);
  float Beta = atan(-A.y / A.x);

  if (A.x < 0) {
    Beta = PI + Beta;
  } else if (A.x >= 0 && A.y < 0) {
    Beta = 2.0f * PI + Beta;
  }

  // tan(alpha + beta) = Numerator / Denominator = OP / AJ
  // then OP = Y = AJ * Numerator / Denominator and
  // AJ = X = OP * Denominator / Numerator

  const float Numerator = Alpha + Beta;
  const float Denominator = 1 - Alpha * Beta;

  return {(A.y * Denominator / Numerator), A.x * Numerator / Denominator};
}



Vector2 Math::Subtract(const Vector2& A, const Vector2& B) {
  return {(A.x - B.x), (A.y - B.y)};
}



Vector2 Math::Add(const Vector2& A, const Vector2& B) {
  return {(B.x + A.x), (B.y + A.y)};
}



Vector2 Math::Normalize(const Vector2& A, const float Mag) {
  return {A.x / Mag, A.y / Mag};
}



Vector2 Math::Multiply(const Vector2& A, const float K) {
  return {A.x * K, A.y * K};
}



float Math::GetMag(const Vector2& A) {
  return sqrtf(powf(A.x, 2) + powf(A.y, 2));
}



bool Math::IsEqual(const Vector2& A, const Vector2& B) {
  return IsEqual(A.x, B.x) && IsEqual(A.y, B.y);
}



bool Math::IsEqual(const float A, const float B) {
  return A >= B - FLT_EPSILON && A <= B + FLT_EPSILON;
}
