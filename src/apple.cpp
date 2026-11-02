#include "apple.h"

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
   DrawTextureV(image, position, WHITE);
}

Vector2 Apple::GetPosition()
{
   return position;
}

void Apple::SetPosition(Vector2 position)
{
   this->position = position;
}