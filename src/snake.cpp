#include "snake.h"

Snake::Snake()
{

}

Vector2 Snake::GetBodySize()
{
   return this->bodySize;
}

Vector2 Snake::GetPositionAt(int index)
{
   return this->body.at(index);
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

void Snake::SetBodySize(Vector2 bodySize)
{
   this->bodySize = bodySize;
}

void Snake::SetBody(std::vector<Vector2> body)
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

void Snake::AddSegment(Vector2 position)
{
   this->body.push_back(position);
}

void Snake::Move(Vector2 displacement)
{
   for (int i = static_cast<int>(body.size()) - 1; i > 0; i--)
   {
      body.at(i) = body.at(i - 1);
   }
   body.at(0).x += displacement.x;
   body.at(0).y += displacement.y;
}