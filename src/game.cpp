#include "game.h"
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
   apple.color = RED;
   timeToDrawSnake = 0;
   isGameOver = false;
   score = 0;
   direction = RIGHT;
   restartGame = false;
   snake.SetBodySize({tileSize, tileSize});
   snake.SetBody({{90, 450}, {60, 450}, {30, 450}});
   snake.SetHeadColor({41, 143, 69, 255});
   snake.SetBodyColor({50, 168, 82, 255});
   GenerateRandomApple();
}

void Game::Update()
{
   HandleRestartGame();

   if (isGameOver)
      return;

   HandleDirection();
   UpdateSnakePosition();
   CheckAppleEaten();
   CheckSelfCollision();
}

void Game::HandleDirection()
{
   Direction prevDir = direction;
   input.CheckDirection(direction);
   if (prevDir != direction)
   {
      queueMoves.push(direction);
   }
}

void Game::HandleRestartGame()
{
   restartGame = input.CheckRestartGame();
   if (restartGame && isGameOver)
   {
      Initialize();
   }
}

void Game::UpdateSnakePosition()
{
   this->timeToDrawSnake += GetFrameTime();
   // std::cout << "Tiempo " << this->timeToDrawSnake;
   if (timeToDrawSnake >= 0.10f)
   {
      CheckBorderCollision();

      timeToDrawSnake = 0;
      Vector2 displacement = {0, 0};
      Direction _direction = direction;
      if (!queueMoves.empty())
      {
         _direction = queueMoves.front();
         queueMoves.pop();
      }

      switch (_direction)
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
      snake.Move(displacement);
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

   for (int i = 1; i < columns; i++)
   {
      DrawLineV({(float)i * tileSize, 0}, {(float)i * tileSize, (float)GetScreenHeight()}, lightGray);
      DrawLineV({0, (float)i * tileSize}, {(float)GetScreenHeight(), (float)i * tileSize}, lightGray);
   }

   DrawRectangleV(apple.position, {tileSize, tileSize}, apple.color);

   DrawRectangleV(snake.GetPositionAt(0), snake.GetBodySize(), snake.GetHeadColor());
   for (int i = 1; i < snake.GetBodyCount(); i++)
   {
      DrawRectangleV(snake.GetPositionAt(i), snake.GetBodySize(), snake.GetBodyColor());
   }

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
   bool applePlacedSuccessfully = true;
   do
   {
      // 1. Obtain a random seed from the hardware
      std::random_device rd;

      // 2. Initialize the Mersenne Twister engine with the seed
      std::mt19937 gen(rd());

      // 3. Define the range (inclusive, e.g., 1 to 30)
      std::uniform_int_distribution<> distr(0, columns - 1);

      // 4. Generate random numbers
      int appleX = distr(gen) * tileSize;
      int appleY = distr(gen) * tileSize;
      apple.position = {(float)appleX, (float)appleY};
      for (int i = 0; i < snake.GetBodyCount(); i++)
      {
         if (appleX == snake.GetPositionAt(i).x &&
             appleY == snake.GetPositionAt(i).y)
         {
            applePlacedSuccessfully = false;
         }
      }
   } while (!applePlacedSuccessfully);
}

void Game::CheckAppleEaten()
{
   Vector2 head = snake.GetPositionAt(0);
   if (head.x == apple.position.x &&
       head.y == apple.position.y)
   {
      GenerateRandomApple();
      if (direction == UP)
      {
         snake.AddSegment({head.x, head.y + tileSize});
      }
      else if (direction == LEFT)
      {
         snake.AddSegment({head.x + tileSize, head.y});
      }
      else if (direction == RIGHT)
      {
         snake.AddSegment({head.x - tileSize, head.y});
      }
      else if (direction == DOWN)
      {
         snake.AddSegment({head.x, head.y - tileSize});
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

void Game::CheckBorderCollision()
{
   Vector2 head = snake.GetPositionAt(0);
   if (head.x == 0 &&
           direction == LEFT ||
       (head.x + tileSize) == GetScreenWidth() &&
           direction == RIGHT ||
       head.y == 0 &&
           direction == UP ||
       (head.y + tileSize) == GetScreenHeight() &&
           direction == DOWN)
   {
      isGameOver = true;
   }
}