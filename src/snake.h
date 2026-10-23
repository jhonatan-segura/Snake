#pragma once

#include "raylib.h"
#include <vector>

class Snake
{
   Vector2 bodySize;
   std::vector<Vector2> body;
   Color headColor;
   Color bodyColor;

public:
   Snake(Vector2 bodySize, std::vector<Vector2> body, Color headColor, Color bodyColor) : bodySize(bodySize), body(body), headColor(headColor), bodyColor(bodyColor) {};
   Vector2 GetBodySize();
   Vector2 GetPositionAt(int index);
   int GetBodyCount();
   Color GetHeadColor();
   Color GetBodyColor();
   void SetBodySize(Vector2 bodySize);
   void AddSegment(Vector2 position);
   void Move(Vector2 displacement);
};