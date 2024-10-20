#pragma once
#include "raylib.h"
#include <list>

namespace Collisions {
enum class WhereCollides;
}
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
  bool f_HasDuplicate;
  DemonType* f_Duplicate;
};



/**
* @brief
*/
void Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition);

/**
 * @brief
 * @param Demon
 * @param Duplicated
 * @param CollisionPlace
 * @param DuplicatedVisible
 * @param DemonDups
 */
void UpdateDuplicate(DemonType& Demon,
                     DemonType& Duplicated,
                     Collisions::WhereCollides CollisionPlace,
                     bool& DuplicatedVisible,
                     std::list<Demon::DemonType>& DemonDups);


void Duplicate(const DemonType& Demon,
                      DemonType& Duplicated,
                      Collisions::WhereCollides CollisionPlace);
/**
 * @brief
 * @param Delta
 */
void Update(std::list<DemonType>& Demons, float Delta);

/**
 * @brief
 * @param Demons
 */
void Draw(std::list<DemonType>& Demons);

};
