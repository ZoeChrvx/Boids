#include "Boids.h"
#include "raymath.h"

Boids::Boids()
{
}

Boids::Boids(float x, float y, float size, int id, Color color)
{
	boidPosition.x = x;
	boidPosition.y = y;
	boidSize = size;
	boidColor = color;
	boidID = id;
	direction = { 1,1 };

}

Boids::~Boids()
{
}

void Boids::SetPosition(float x, float y)
{
	boidPosition.x = x;
	boidPosition.y = y;
}
void Boids::Move(Vector2 move)
{

	move = Vector2Normalize(move);

	boidPosition = Vector2Add(boidPosition, move);
}

Vector2 Boids::Detection(std::vector<Boids*>& boidList)
{
	Vector2 finalDir = Vector2Zero();
	for (Boids* b : boidList) 
	{
		if (b->boidID == boidID) {
			continue;
		}
		float currentDistance =  Vector2Distance(b->boidPosition, boidPosition);
		if (currentDistance < minimumDistance) {
			Vector2 newDirection = Vector2Subtract(boidPosition, b->boidPosition);
			newDirection = Vector2Normalize(newDirection);
			finalDir = Vector2Add(finalDir, newDirection);
		}
	}

	if (boidPosition.x <= boidSize / 2) finalDir.x = 2;
	if (boidPosition.x >= 800 - boidSize / 2) finalDir.x = -2;
	if (boidPosition.y <= boidSize / 2) finalDir.y = 2;
	if (boidPosition.y >= 800 - boidSize / 2) 
		finalDir.y = -2;

	return Vector2Normalize(finalDir);
}

void Boids::Draw()
{
	DrawCircle((int)boidPosition.x, (int)boidPosition.y, boidSize, boidColor);
}

int Boids::getID() {
	return boidID;
}

void Boids::Update(std::vector<Boids*> &boidList)
{
	Vector2 speedMove = Vector2Zero();
	speedMove = Vector2Add(speedMove, Detection(boidList));
	if (Vector2Length(speedMove) <= 0) {
		speedMove = direction;
	}
	Move(Vector2Normalize(speedMove));
	direction = speedMove;
}




