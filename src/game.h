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
   float timeToDrawSnake;
   enum Direction direction;
   bool isGameOver;
   int score;
   std::queue<Direction> queueMoves;

   Input input;
   Snake snake;
   Apple apple;

public:
   Game();
   void Initialize();
   void Update();
   void HandleDirection();
   void HandleRestartGame();
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