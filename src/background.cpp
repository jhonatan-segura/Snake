#include "background.h"

Background::Background()
{
   image = LoadTexture("assets/graphics/grass.png");
}

Background::~Background()
{
   UnloadTexture(image);
}

void Background::Draw()
{
   DrawTexturePro(image, {0, 0, (float)image.width, (float)image.height}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);
}
