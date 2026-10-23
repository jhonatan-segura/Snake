#pragma once

#include "raylib.h"
#include "direction.h"

class Input
{
public:
   void HandleInput();
   void CheckDirection(Direction& direction);
};