#include "Collisions.h"



bool Collisions::IsCircleCircle(const Vector2& APosition,
                                float ARadius,
                                const Vector2& BPosition,
                                float BRadius) {
  const float k_Dist = (APosition.x - BPosition.x) * (APosition.x - BPosition.x)
                       + (APosition.y - BPosition.y) * (
                         APosition.y - BPosition.y);
  const float k_Radii = (ARadius + BRadius) * (ARadius + BRadius);

  // Sum(Radius)^2 >= Dist^2
  // saves the necessity of a sqrt
  return k_Radii >= k_Dist;
}
