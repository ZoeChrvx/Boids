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
	maxPerceiveDistance = boidSize * 6;
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

	boidPosition = Vector2Clamp(Vector2Add(boidPosition, Vector2Scale(move, 5.f)), { 20,20 }, { 1900, 1060 });
}

Vector2 Boids::Detection(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList)
{
	Vector2 separation = Vector2Zero(), avoidance = Vector2Zero();
	for (Boids* b : boidList)
	{
		if (b->boidID == boidID) {
			continue;
		}
		float currentDistance = Vector2Distance(b->boidPosition, boidPosition);
		if (currentDistance < minimumDistance) {
			Vector2 newDirection = Vector2Subtract(boidPosition, b->boidPosition);
			newDirection = Vector2Normalize(newDirection);
			separation = Vector2Add(separation, newDirection);
		}
	}
	separation = Vector2Normalize(separation);

	for (Obstacles* o : obstList)
	{
		bool isCollision = CheckCollisionCircleRec(boidPosition, boidSize * 10.f, o->GetRectangle());
		if (isCollision)
		{
			Vector2 newDirection = Vector2Invert(Vector2Subtract(boidPosition, { o->GetRectangle().x, o->GetRectangle().y }));
			newDirection = Vector2Normalize(newDirection);
			avoidance = Vector2Add(avoidance, newDirection);
		}
	}
	avoidance = Vector2Normalize(avoidance);

	return Vector2Normalize(Vector2Add(Vector2Scale(separation, 0.3f), Vector2Scale(avoidance, 0.7f)));
}

void Boids::Draw()
{
	DrawCircle((int)boidPosition.x, (int)boidPosition.y, boidSize, boidColor);
}

int Boids::GetID() {
	return boidID;
}

void Boids::Update(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList)
{
	Vector2 speedMove = direction;
	speedMove = Vector2Add(speedMove, Vector2Scale(Detection(boidList, obstList), 0.8f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Aligment(boidList), 0.4f));
	if (Vector2Length(speedMove) <= 0) {
		speedMove = direction;
	}
	direction = Vector2Normalize(speedMove);
	Move(direction);

}

Vector2 Boids::Aligment(std::vector<Boids*>& boidList)
{
	Vector2 directionTotal = Vector2Zero();
	int count=0;
	for (Boids* b : boidList)
	{
		if (b->boidID == boidID) {
			continue;
		}
		float currentDistance = Vector2Distance(b->boidPosition, boidPosition);
		if (currentDistance < maxPerceiveDistance) 
		{
			directionTotal = Vector2Add(directionTotal, b->direction);
			count++;
		}
	}
	if(count != 0)
		directionTotal = Vector2{ directionTotal.x / count, directionTotal.y / count };

	return Vector2Normalize(directionTotal);
}




