#include "raylib.h"
#include "game.h"
#include "constants.h"

int main(void)
{
   InitWindow(screenWidth, screenHeight, "SNAKE");

   SetTargetFPS(60);

   Game game;
   while (!WindowShouldClose())
   {
      game.Update();
      game.Draw();
   }

   CloseWindow();

   return 0;
}