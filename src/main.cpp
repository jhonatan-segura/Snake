#include "raylib.h"
#include "game.h"

int main(void)
{
   InitWindow(900, 900, "SNAKE");

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