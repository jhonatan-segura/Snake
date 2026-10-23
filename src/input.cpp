#include "input.h"

bool Input::CheckRestartGame()
{
   if (IsKeyPressed(KEY_R))
   {
      return true;
   }
   return false;
}

void Input::CheckDirection(Direction &direction)
{
   if (IsKeyPressed(KEY_W) && direction != DOWN)
   {
      direction = UP;
   }
   else if (IsKeyPressed(KEY_A) && direction != RIGHT)
   {
      direction = LEFT;
   }
   else if (IsKeyPressed(KEY_S) && direction != UP)
   {
      direction = DOWN;
   }
   else if (IsKeyPressed(KEY_D) && direction != LEFT)
   {
      direction = RIGHT;
   }
}