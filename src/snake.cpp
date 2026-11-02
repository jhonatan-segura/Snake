#include "snake.h"
#include <iostream>

Snake::Snake()
{
   headImage = LoadTexture("assets/graphics/snake-head.png");
   bodyImage = LoadTexture("assets/graphics/body.png");
   tailImage = LoadTexture("assets/graphics/tail.png");
   jointImage = LoadTexture("assets/graphics/joint.png");
}

Snake::~Snake()
{
   UnloadTexture(headImage);
}

float GetRotationFromDirection(Direction dir)
{
   switch (dir)
   {
   case UP:
      return 270.0f;
   case DOWN:
      return 90.0f;
   }
   return 0.0f;
}

void Snake::Draw()
{
   Vector2 headPos = body[0].position;
   Direction headDir = body[0].direction;
   float headWidth = (float)headImage.width;
   DrawTexturePro(headImage, {0, 0, headDir == LEFT ? headWidth * -1 : headWidth, (float)headImage.height}, {headPos.x + 15, headPos.y + 15, 30, 30}, {15, 15}, GetRotationFromDirection(headDir), WHITE);

   for (int i = 1; i < body.size() - 1; i++)
   {
      if (body[i].isJoint)
      {
         DrawTexturePro(jointImage, {0, 0, headWidth, (float)headImage.height}, {body[i].position.x + 15, body[i].position.y + 15, 30, 30}, {15, 15}, body[i].rotationAngle, WHITE);
      }
      else
      {
         DrawTexturePro(bodyImage, {0, 0, body[i].direction == LEFT ? headWidth * -1 : headWidth, (float)bodyImage.height}, {body[i].position.x + 15, body[i].position.y + 15, 30, 30}, {15, 15}, GetRotationFromDirection(body[i].direction), WHITE);
      }
   }
   Vector2 tailPos = body[body.size() - 1].position;
   Direction tailDir = body[body.size() - 1].direction;
   DrawTexturePro(tailImage, {0, 0, tailDir == LEFT ? headWidth * -1 : headWidth, (float)tailImage.height}, {tailPos.x + 15, tailPos.y + 15, 30, 30}, {15, 15}, GetRotationFromDirection(tailDir), WHITE);
}

Vector2 Snake::GetBodySize()
{
   return this->bodySize;
}

Vector2 Snake::GetPositionAt(int index)
{
   return this->body.at(index).position;
}

int Snake::GetBodyCount()
{
   return this->body.size();
}

Color Snake::GetHeadColor()
{
   return this->headColor;
}

Color Snake::GetBodyColor()
{
   return this->bodyColor;
}

BodyPart Snake::GetTail()
{
   return this->body.at(body.size() - 1);
}

void Snake::SetBodySize(Vector2 bodySize)
{
   this->bodySize = bodySize;
}

void Snake::SetBody(std::vector<BodyPart> body)
{
   this->body = body;
}

void Snake::SetHeadColor(Color headColor)
{
   this->headColor = headColor;
}

void Snake::SetBodyColor(Color bodyColor)
{
   this->bodyColor = bodyColor;
}

void Snake::AddSegment(BodyPart bodyPart)
{
   this->body.push_back(bodyPart);
}

float GetRotationFromJoint(Direction a, Direction b)
{
   // std::cout << "a, b: " << a << " " << b << std::endl;
   if (a == DOWN && b == LEFT || a == RIGHT && b == UP)
   {
      return 90.0f;
   }
   else if (a == DOWN && b == RIGHT || a == LEFT && b == UP)
   {
      return 180.0f;
   }
   else if (a == LEFT && b == DOWN || a == UP && b == RIGHT)
   {
      return 270.0f;
   }
   return 0.0f;
}

void Snake::Move(Vector2 displacement, Direction dir)
{
   body.at(0).direction = dir;
   for (int i = static_cast<int>(body.size()) - 1; i > 0; i--)
   {
      bool isJoint = false;
      float rotationAngle = 0.0f;
      if (body.at(i).direction != body.at(i - 1).direction)
      {
         isJoint = true;
         rotationAngle = GetRotationFromJoint(body.at(i).direction, body.at(i - 1).direction);
      }
      body.at(i) = body.at(i - 1);
      body.at(i).isJoint = isJoint;
      body.at(i).rotationAngle = rotationAngle;
   }
   body.at(0).position.x += displacement.x;
   body.at(0).position.y += displacement.y;
}