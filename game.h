#pragma once

#include "raylib.h"
#include "snake.h"
#include "direction.h"
#include "input.h"
#include "apple.h"
#include <queue>

class Game
{
private:
   const int screenWidth = 900;
   const int screenHeight = 900;
   const float columns = 30.0f;
   const float tileSize = screenWidth / columns;
   Color backgroundColor;
   Color lightGray;
   float timeToDrawSnake = 0;
   // float lastTimeInputPressed = 0;
   enum Direction direction = RIGHT;
   bool isGameOver = false;
   int score = 0;
   std::queue<Direction> queueMoves;

   Input input;
   Snake snake;
   Apple apple;

public:
   Game();
   void Update();
   void HandleInput();
   void UpdateSnakePosition();
   void Draw();
   void SetTimeToDrawTile(float time);
   float GetTimeToDrawTile();
   Color GetBackgroundColor();
   int GetScreenWidth();
   int GetScreenHeight();
   void GenerateRandomApple();
   void CheckAppleEaten();
   void CheckSelfCollision();
   void CheckBorderCollision();
};