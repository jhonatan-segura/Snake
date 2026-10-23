#include "raylib.h"
#include "game.h"

int main(void)
{
   Game game;
   InitWindow(game.GetScreenWidth(), game.GetScreenHeight(), "SNAKE");

   SetTargetFPS(60);

   while (!WindowShouldClose())
   {
      game.Update();
      game.Draw();
   }

   // De-Initialization
   CloseWindow(); // Close window and OpenGL context

   return 0;
}