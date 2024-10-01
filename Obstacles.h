#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"

class Obstacles
{
public:
	Obstacles();
	Obstacles(Rectangle obstacle, Color color);
	~Obstacles();
	Rectangle GetRectangle();

	void Draw();

private:
	Rectangle obstRectangle{0,0,0,0};
	Vector2 obstPosition = Vector2One();
	Vector2 obstSize = Vector2Zero();
	Vector2 obstCenter;
	Color obstColor;

};

