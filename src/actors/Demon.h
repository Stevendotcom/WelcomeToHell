#pragma once
#include <list>

#include "raylib.h"
#include "engine/Animations.h"

#include "engine/Collisions.h"

namespace Demon {

struct DemonType {
  Vector2 f_Position;
  Vector2 f_Direction;
  float f_Speed;
  float f_Radius;
  float f_FrameTime;
  Texture f_Sprite;
  Animations::Frame f_Frame;
  int f_FrameIndex;
  int f_Id;
  DemonType* f_Duplicate;
};



void ChangeDirection(DemonType& Demon);

void DivideDemon(DemonType& Demon, std::list<DemonType>& Demons);

void Initialize(std::list<DemonType>& Demons, const Vector2& PlayerPosition);


void UpdateDuplicate(DemonType& Demon,
                     DemonType* Duplicated,
                     Collisions::WhereCollides CollisionPlace);

void Duplicate(const DemonType& Demon,
               DemonType* Duplicated,
               Collisions::WhereCollides CollisionPlace);

void Clear(std::list<DemonType>& Demons);

void Execute(std::list<DemonType>& Demons);


void Update(std::list<DemonType>& Demons, float Delta);


void Draw(const DemonType& Demon);

};
