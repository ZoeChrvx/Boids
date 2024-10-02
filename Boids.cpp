#include "Boids.h"
#include "raymath.h"

Boids::Boids()
{
}

Boids::Boids(float x, float y, float size, int id, int equip, Color color, Texture2D texture)
{
	boidPosition.x = x;
	boidPosition.y = y;
	boidSize = size;
	boidColor = color;
	boidID = id;
	direction = { 1,1 };
	minimumDistance = boidSize * 2;
	maxPerceiveDistance = boidSize * 10;
	cohesionRadius = boidSize * 30;
	boidTexture = texture;
	boidEquip = equip;
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

	boidPosition = Vector2Clamp(Vector2Add(boidPosition, Vector2Scale(move, 3.f)), { 20,20 }, { 1900, 1060 });
}

Vector2 newDirection;



void Boids::Draw()
{
	//DrawCircle((int)boidPosition.x, (int)boidPosition.y, boidSize, boidColor);
	float angle = Vector2Angle({ -1,0 }, direction) * (-180.f / PI);
	DrawTexturePro(boidTexture, { 0,0, float(boidTexture.height),float(boidTexture.width) }, { boidPosition.x, boidPosition.y, boidSize, boidSize }, { boidSize / 2, boidSize / 2 }, angle, boidColor);

	if (boidEquip == 1) {
		SetColor(DARKBLUE);
	}
	else if (boidEquip == 2) {
		SetColor(DARKGREEN);
	}
	else {
		SetColor(DARKPURPLE);
	}
}

int Boids::GetID() {
	return boidID;
}

int Boids::GetEquip()
{
	return boidEquip;
}

void Boids::SetColor(Color color)
{
	boidColor = color;
}

void Boids::Update(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList)
{
	Vector2 speedMove = direction;
	speedMove = Vector2Add(speedMove, Vector2Scale(Avoid(boidList), 0.5f));
	speedMove = Vector2Add(speedMove, Vector2Scale(AvoidObstacles(obstList), 0.7f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Aligment(boidList), 0.5f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Group(boidList), 0.05f));
	speedMove = Vector2Add(speedMove, Vector2Scale(AvoidMouse(), 0.7f));
	if (Vector2Length(speedMove) <= 0) {
		//speedMove = direction;
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

Vector2 Boids::Group(std::vector<Boids*>& boidList)
{
	Vector2 positionTotal = Vector2Zero();
	int count = 0;
	for (Boids* b : boidList) 
	{
		if(b->boidID==boidID)
		{
			continue;
		}
		float currentDistance = Vector2Distance(b->boidPosition, boidPosition);
		if (currentDistance < cohesionRadius) {
			newDirection = Vector2Subtract(b->boidPosition, boidPosition);
			newDirection = Vector2Normalize(newDirection);
			positionTotal = Vector2Add(positionTotal, newDirection);
			count++;
		}
	}
	if (count != 0)
	{
		positionTotal = Vector2{ positionTotal.x / count, positionTotal.y / count };
	}

	return Vector2Normalize(positionTotal);
}

Vector2 Boids::Avoid(std::vector<Boids*>& boidList)
{
	Vector2 separation = Vector2Zero();
	for (Boids* b : boidList)
	{
		if (b->boidID == boidID) {
			continue;
		}
		float currentDistance = Vector2Distance(b->boidPosition, boidPosition);
		if (currentDistance < minimumDistance) {
			newDirection = Vector2Subtract(boidPosition, b->boidPosition);
			newDirection = Vector2Normalize(newDirection);
			separation = Vector2Add(separation, newDirection);
		}
	}
	separation = Vector2Normalize(separation);

	return separation;
}

Vector2 Boids::AvoidObstacles(std::vector<Obstacles*>& obstacleList)
{
	Vector2 avoidance = Vector2Zero();
	for (Obstacles* o : obstacleList)
	{
		bool isCollision = CheckCollisionCircleRec(boidPosition, boidSize * 5.f, o->GetRectangle());
		if (isCollision)
		{
			Vector2 newDirection = Vector2Invert(Vector2Subtract(boidPosition, { o->GetRectangle().x, o->GetRectangle().y }));
			newDirection = Vector2Normalize(newDirection);
			avoidance = Vector2Add(avoidance, newDirection);
		}
	}
	avoidance = Vector2Normalize(avoidance);

	return avoidance;
}

Vector2 Boids::AvoidMouse() 
{
	Vector2 mouse = GetMousePosition();
	Vector2 separation = Vector2Zero();
	
	float currentDistance = Vector2Distance(mouse, boidPosition);
	if (currentDistance < 100)
	{
		separation = Vector2Subtract(boidPosition, mouse);
	}
	separation = Vector2Normalize(separation);

	return separation;
}





