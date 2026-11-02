#include "apple.h"
#include "constants.h"

Apple::Apple() 
{
   image = LoadTexture("assets/graphics/apple.png");
   color = RED;
}

Apple::~Apple()
{
   UnloadTexture(image);
}

void Apple::Draw()
{
   DrawTexturePro(image, {0, 0, (float)image.width, (float)image.height}, {position.x, position.y, tileSize, tileSize}, {0, 0}, 0, WHITE);
}

Vector2 Apple::GetPosition()
{
   return position;
}

void Apple::SetPosition(Vector2 position)
{
   this->position = position;
}