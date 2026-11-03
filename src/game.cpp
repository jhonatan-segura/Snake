#include "game.h"
#include "constants.h"
#include <iostream>
#include <random>

Game::Game()
{
   Initialize();
}

void Game::Initialize()
{
   backgroundColor = {25, 25, 25, 255};
   lightGray = {70, 70, 70, 255};
   timeToDrawSnake = 0;
   isGameOver = false;
   score = 0;
   headDirection = RIGHT;
   snake.SetBodySize({tileSize, tileSize});
   snake.SetBody({{{tileSize * 3, tileSize}, RIGHT}, {{tileSize * 2, tileSize}, RIGHT}, {{tileSize, tileSize}, RIGHT}});
   snake.SetHeadColor({41, 143, 69, 255});
   snake.SetBodyColor({50, 168, 82, 255});
   GenerateRandomApple();
   ClearQueueMoves(queueMoves);
}

void Game::ClearQueueMoves(std::queue<Direction> &q)
{
   std::queue<Direction>().swap(q);
}

void Game::Update()
{
   if (isGameOver)
   {
      HandleRestartGame();
      return;
   }

   HandleDirection();
   UpdateSnakePosition();
   CheckAppleEaten();
   CheckSelfCollision();
}

void Game::HandleDirection()
{
   Direction prevDir = headDirection;
   input.CheckDirection(headDirection);
   if (prevDir != headDirection)
   {
      queueMoves.push(headDirection);
   }
}

void Game::HandleRestartGame()
{
   if (input.CheckRestartGame())
   {
      Initialize();
   }
}

void Game::UpdateSnakePosition()
{
   this->timeToDrawSnake += GetFrameTime();

   float snakeDrawSpeed = 0.11f;
   if (timeToDrawSnake >= snakeDrawSpeed)
   {
      if (CollisionOnBorder())
      {
         return;
      }

      timeToDrawSnake = 0;
      Vector2 displacement = {0, 0};
      if (!queueMoves.empty())
      {
         headDirection = queueMoves.front();
         queueMoves.pop();
      }

      switch (headDirection)
      {
      case UP:
         displacement.y = -tileSize;
         break;
      case LEFT:
         displacement.x = -tileSize;
         break;
      case RIGHT:
         displacement.x = tileSize;
         break;
      case DOWN:
         displacement.y = tileSize;
         break;
      }
      snake.Move(displacement, headDirection);
      // std::cout << "pos snake " << (int)snake.GetPositionAt(0).x << " " << snake.GetPositionAt(0).x << (int)snake.GetPositionAt(0).y << " " << snake.GetPositionAt(0).y << std::endl;
      // std::cout << "pos apple " << (int)apple.position.x << " " << (int)apple.position.y << std::endl;
      // bool eval1 = (int)snake.GetPositionAt(0).x == (int)apple.position.x;
      // std::cout << "x eval " << eval1;
      // bool eval2 = (int)snake.GetPositionAt(0).y == (int)apple.position.y;
      // std::cout << "y eval " << eval2;
   }
}

void Game::Draw()
{
   BeginDrawing();

   ClearBackground(backgroundColor);

   // for (int i = 1; i < columns; i++)
   // {
   //    DrawLineV({(float)i * tileSize, 0}, {(float)i * tileSize, (float)GetScreenHeight()}, lightGray);
   //    DrawLineV({0, (float)i * tileSize}, {(float)GetScreenHeight(), (float)i * tileSize}, lightGray);
   // }
   background.Draw();

   // DrawRectangleV(apple.position, {tileSize, tileSize}, apple.color);
   apple.Draw();

   snake.Draw();

   if (isGameOver)
   {
      const char *text = TextFormat("Score %d", score);
      int fontSize = 45;
      DrawText(text, GetScreenWidth() / 2.0f - MeasureText(text, fontSize) / 2.0f, GetScreenHeight() / 2.0f - fontSize / 2.0f, fontSize, RAYWHITE);
   }

   EndDrawing();
}

Color Game::GetBackgroundColor()
{
   return this->backgroundColor;
}

float Game::GetTimeToDrawTile()
{
   return this->timeToDrawSnake;
}

void Game::SetTimeToDrawTile(float time)
{
   this->timeToDrawSnake = time;
}

int Game::GetScreenWidth()
{
   return screenWidth;
}

int Game::GetScreenHeight()
{
   return screenHeight;
}

void Game::GenerateRandomApple()
{
   bool applePlacedSuccessfully;
   // 1. Obtain a random seed from the hardware
   std::random_device rd;

   // 2. Initialize the Mersenne Twister engine with the seed
   std::mt19937 gen(rd());

   // 3. Define the range (inclusive, e.g., 1 to columns)
   std::uniform_int_distribution<> distr(0, columns - 1);
   do
   {
      // 4. Generate random numbers
      int appleX = distr(gen) * tileSize;
      int appleY = distr(gen) * tileSize;
      apple.SetPosition({(float)appleX, (float)appleY});

      applePlacedSuccessfully = true;

      for (int i = 0; i < snake.GetBodyCount(); i++)
      {
         if (appleX == snake.GetPositionAt(i).x &&
             appleY == snake.GetPositionAt(i).y)
         {
            applePlacedSuccessfully = false;
            continue;
         }
      }
   } while (!applePlacedSuccessfully);
}

void Game::CheckAppleEaten()
{
   Vector2 head = snake.GetPositionAt(0);
   BodyPart tail = snake.GetTail();
   if (head.x == apple.GetPosition().x &&
       head.y == apple.GetPosition().y)
   {
      GenerateRandomApple();
      switch (tail.direction)
      {
      case UP:
         snake.AddSegment({{tail.position.x, tail.position.y + tileSize}, UP});
         break;
      case LEFT:
         snake.AddSegment({{tail.position.x + tileSize, tail.position.y}, LEFT});
         break;
      case RIGHT:
         snake.AddSegment({{tail.position.x - tileSize, tail.position.y}, RIGHT});
         break;
      case DOWN:
         snake.AddSegment({{tail.position.x, tail.position.y - tileSize}, DOWN});
         break;
      }
      score++;
      // std::cout << "snake size " << snake.GetBodyCount() << std::endl;
   }
}

void Game::CheckSelfCollision()
{
   Vector2 head = snake.GetPositionAt(0);
   for (int i = 3; i < snake.GetBodyCount(); i++)
   {
      if (head.x == snake.GetPositionAt(i).x &&
          head.y == snake.GetPositionAt(i).y)
      {
         isGameOver = true;
      }
   }
}

bool Game::CollisionOnBorder()
{
   Vector2 head = snake.GetPositionAt(0);
   if (head.x == 0 &&
           headDirection == LEFT ||
       (head.x + tileSize) == GetScreenWidth() &&
           headDirection == RIGHT ||
       head.y == 0 &&
           headDirection == UP ||
       (head.y + tileSize) == GetScreenHeight() &&
           headDirection == DOWN)
   {
      std::cout << "border colission" << std::endl;
      isGameOver = true;
      return isGameOver;
      // exit(1);
   }
   return false;
}