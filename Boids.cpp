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
	minimumDistance = boidSize * 2;
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

	//move = Vector2Normalize(move);

	boidPosition = Vector2Add(boidPosition, Vector2Scale(move, 5.f));
}

Vector2 Boids::Detection(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList)
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

	for (Obstacles* o : obstList) 
	{
		bool isCollision = CheckCollisionCircleRec(boidPosition, boidSize * 4.f, o->GetRectangle());
		if (isCollision) 
		{
			Vector2 newDirection = Vector2Invert(Vector2Subtract(boidPosition, {o->GetRectangle().x, o->GetRectangle().y}));
			newDirection = Vector2Normalize(newDirection);
			finalDir = Vector2Add(finalDir, newDirection);
		}
	}

	return Vector2Normalize(finalDir);
}

void Boids::Draw()
{
	DrawCircle((int)boidPosition.x, (int)boidPosition.y, boidSize, boidColor);
}

int Boids::getID() {
	return boidID;
}

void Boids::Update(std::vector<Boids*> &boidList, std::vector<Obstacles*> &obstList)
{
	Vector2 speedMove = direction;
	speedMove = Vector2Add(speedMove, Detection(boidList, obstList));
	if (Vector2Length(speedMove) <= 0) {
		speedMove = direction;
	}
	direction = Vector2Normalize(speedMove);
	Move(direction);
	
}




