#pragma once
#include <raylib.h>

namespace Animations {


using Frame = Rectangle;


bool Update(Frame& Frame,
            int Rows,
            int Cols,
            int& FrameIndex,
            float& FrameTime,
            float Delta,
            const Vector2& SpriteSize);
};
