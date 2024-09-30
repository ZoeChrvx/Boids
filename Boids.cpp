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
	direction = { 1,1 };
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
	if (boidX <= boidSize / 2) direction.x += 2;
	if (boidX >= 800 - boidSize / 2) direction.x -= 2;
	if (boidY <= boidSize / 2) direction.y += 2;
	if (boidY >= 800 - boidSize / 2) direction.y -= 2;


	direction = Vector2Normalize(direction);

	boidX += direction.x;
	boidY += direction.y;
}

void Boids::Draw()
{
	DrawCircle((int)boidX, (int)boidY, boidSize, boidColor);
}



