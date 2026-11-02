#pragma once

#include "raylib.h"

class Apple {
private:
   Vector2 position;
   Color color;
   Texture2D image;

public: 
   Apple();
   ~Apple();
   void Draw();
   void SetPosition(Vector2 position);
   Vector2 GetPosition();
};