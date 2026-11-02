#pragma once

#include "raylib.h"
#include "bodypart.h"
#include <vector>

class Snake
{
private:
   Vector2 bodySize;
   std::vector<BodyPart> body;
   Color headColor;
   Color bodyColor;
   Texture2D headImage;
   Texture2D bodyImage;
   Texture2D tailImage;
   Texture2D jointImage;

public:
   Snake();
   ~Snake();
   Snake(Vector2 bodySize, std::vector<BodyPart> body, Color headColor, Color bodyColor) : bodySize(bodySize), body(body), headColor(headColor), bodyColor(bodyColor) {};
   void Draw();
   Vector2 GetBodySize();
   Vector2 GetPositionAt(int index);
   int GetBodyCount();
   Color GetHeadColor();
   Color GetBodyColor();
   BodyPart GetTail();
   void SetBodySize(Vector2 bodySize);
   void SetBody(std::vector<BodyPart> body);
   void SetHeadColor(Color headColor);
   void SetBodyColor(Color bodyColor);
   void AddSegment(BodyPart bodyPart);
   void Move(Vector2 displacement, Direction dir);
};