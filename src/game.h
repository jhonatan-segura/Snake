#pragma once

#include "raylib.h"
#include "snake.h"
#include "direction.h"
#include "input.h"
#include "apple.h"
#include "background.h"
#include <queue>

class Game
{
private:
   Color backgroundColor;
   Color lightGray;
   float timeToDrawSnake;
   enum Direction headDirection;
   bool isGameOver;
   int score;
   std::queue<Direction> queueMoves;

   Input input;
   Background background;
   Snake snake;
   Apple apple;

public:
   Game();
   void Initialize();
   void Update();
   void HandleDirection();
   void ClearQueueMoves(std::queue<Direction> &q);
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
   bool CollisionOnBorder();
};