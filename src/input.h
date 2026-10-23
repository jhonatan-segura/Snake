#pragma once

#include "raylib.h"
#include "direction.h"

class Input
{
public:
   bool CheckRestartGame();
   void CheckDirection(Direction &direction);
};