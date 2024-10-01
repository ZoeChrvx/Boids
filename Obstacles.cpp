#include "Obstacles.h"

Obstacles::Obstacles()
{
}

Obstacles::Obstacles(Rectangle rectangle, Color color)
{
	obstRectangle = rectangle;
	obstColor = color;
}

Obstacles::~Obstacles()
{
}

Rectangle Obstacles::GetRectangle()
{
	return obstRectangle;
}

void Obstacles::Draw()
{
    DrawRectangleRec(obstRectangle, obstColor);
}
