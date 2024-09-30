#include "Boids.h"

Boids::Boids()
{
}

Boids::Boids(float x, float y, float size, Color color)
{
	boidX = x;
	boidY = y;
	boidSize = size;
	boidColor = color;
}

Boids::~Boids()
{
}

void Boids::SetPosition(float x, float y)
{
	boidX = x;
	boidY = y;
}
void Boids::Move(Vector2 move)
{
	boidX += move.x;
	boidY += move.y;
}

void Boids::Draw()
{
	DrawCircle((int)boidX, (int)boidY, boidSize, boidColor);
}



