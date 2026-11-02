#pragma once

#include "raylib.h"
#include "direction.h"

struct BodyPart
{
   Vector2 position;
   Direction direction;
   float rotationAngle;
   bool isJoint;
};