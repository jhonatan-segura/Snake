#pragma once

#include "raylib.h"

class Background {
private:
   Texture2D image;

public: 
   Background();
   ~Background();
   void Draw();
};