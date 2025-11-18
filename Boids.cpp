#include "Boids.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>

Boids::Boids(float x, float y, float size, int id, int equip, int enemyEquip, Color color, Texture2D texture) : mIsAlive{true}, mSpeed{150.f}, mDirection{Vector2One()}, mPosition{0.f}
{
	mPosition.x = x;
	mPosition.y = y;
	mSize = size;
	mColor = color;
	mID = id;
	mDirection = { 1,1 };
	minimumDistance = mSize * 2;
	maxPerceiveDistance = mSize * 10;
	cohesionRadius = mSize * 30;
	mTexture = texture;
	mTeam = equip;
	mEnemyTeam = enemyEquip;
}

Boids::~Boids()
{
}

void Boids::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
}
void Boids::Move(Vector2 move)
{

	//move = Vector2Normalize(move);

	// boidPosition = Vector2Clamp(Vector2Add(boidPosition, Vector2Scale(move, 3.f)), { 20,20 }, { 1900, 1060 });
	mPosition = Vector2Add(mPosition, Vector2Scale(move, 3.f));
}

Vector2 newDirection;



void Boids::Draw()
{
	//DrawCircle((int)boidPosition.x, (int)boidPosition.y, boidSize, boidColor);
	float angle = Vector2Angle({ -1,0 }, mDirection) * (-180.f / PI);
	DrawTexturePro(mTexture, { 0,0, float(mTexture.height),float(mTexture.width) }, { mPosition.x, mPosition.y, mSize, mSize }, { mSize / 2, mSize / 2 }, angle, mColor);

	if (mTeam == 1) {
		SetColor(DARKBLUE);
	}
	else if (mTeam == 2) {
		SetColor(DARKGREEN);
	}
	else {
		SetColor(DARKPURPLE);
	}
}

int Boids::GetID() {
	return mID;
}

int Boids::GetEquip()
{
	return mTeam;
}

void Boids::SetColor(Color color)
{
	mColor = color;
}

void Boids::Update(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList)
{
	Vector2 speedMove = Vector2Zero();
	speedMove = Vector2Add(speedMove, Vector2Scale(Avoid(boidList), 0.5f));
	speedMove = Vector2Add(speedMove, Vector2Scale(AvoidObstacles(obstList), 1000.f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Aligment(boidList), 0.6f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Group(boidList), 0.05f));
	speedMove = Vector2Add(speedMove, Vector2Scale(AvoidMouse(), 0.9f));
	speedMove = Vector2Add(speedMove, Vector2Scale(AvoidPredator(boidList), .2f));
	speedMove = Vector2Add(speedMove, Vector2Scale(Attack(boidList), 0.8f));
	if (Vector2Length(speedMove) <= 0) {
		//speedMove = direction;
	}
	speedMove = Vector2Normalize(speedMove);
	mDirection = Vector2Normalize(Vector2Add(mDirection, speedMove));
	Move(mDirection);
}

Vector2 Boids::Aligment(std::vector<Boids*>& boidList)
{
	Vector2 directionTotal = Vector2Zero();
	int count=0;
	for (Boids* b : boidList)
	{
		if (b->mID == mID) {
			continue;
		}
		if (b->GetEquip() == mTeam) {
			float currentDistance = Vector2Distance(b->mPosition, mPosition);
			if (currentDistance < maxPerceiveDistance)
			{
				directionTotal = Vector2Add(directionTotal, b->mDirection);
				count++;
			}
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
		if(b->mID==mID)
		{
			continue;
		}
		if (b->GetEquip() == mTeam) {
			float currentDistance = Vector2Distance(b->mPosition, mPosition);
			if (currentDistance < cohesionRadius) {
				newDirection = Vector2Subtract(b->mPosition, mPosition);
				newDirection = Vector2Normalize(newDirection);
				positionTotal = Vector2Add(positionTotal, newDirection);
				count++;
			}
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
		if (b->mID == mID) {
			continue;
		}

		float currentDistance = Vector2Distance(b->mPosition, mPosition);
		if (currentDistance < minimumDistance) {
			newDirection = Vector2Subtract(mPosition, b->mPosition);
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
		bool isCollision = IsCollidingAabb(o->GetRectangle(), 20.f);//CheckCollisionCircleRec(boidPosition, boidSize * 5.f, o->GetRectangle());
		if (isCollision)
		{
			Vector2 newDirection = Vector2Invert(Vector2Subtract(mPosition, { o->GetRectangle().x, o->GetRectangle().y }));
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
	
	float currentDistance = Vector2Distance(mouse, mPosition);
	if (currentDistance < 100)
	{
		separation = Vector2Subtract(mPosition, mouse);
	}
	separation = Vector2Normalize(separation);

	return separation;
}

Vector2 Boids::AvoidPredator(std::vector<Boids*>& boidList)
{
	Vector2 separation = Vector2Zero();
	for (Boids* b : boidList)
	{
		if (b->mID == mID) {
			continue;
		}
		if (b->GetEquip() == mEnemyTeam) {
			float currentDistance = Vector2Distance(b->mPosition, mPosition);
			if (currentDistance < minimumDistance*5.f) {
				newDirection = Vector2Subtract(mPosition, b->mPosition);
				newDirection = Vector2Normalize(newDirection);
				separation = Vector2Add(separation, newDirection);
			}
		}
	}
	separation = Vector2Normalize(separation);

	return separation;
}

Vector2 Boids::Attack(std::vector<Boids*>& boidList)
{
	Vector2 positionTotal = Vector2Zero();
	int count = 0, boidIndex = 0;
	for (Boids* b : boidList)
	{
		if (b->mID == mID)
		{
			boidIndex ++;
			continue;
		}
		if (b->GetEquip() != mTeam && b->GetEquip() != mEnemyTeam) 
		{
			float currentDistance = Vector2Distance(b->mPosition, mPosition);
			if (currentDistance < mSize * 10.f) {
				newDirection = Vector2Subtract(b->mPosition, mPosition);
				newDirection = Vector2Normalize(newDirection);
				positionTotal = Vector2Add(positionTotal, newDirection);
				if (currentDistance < mSize* 3.f && Vector2DotProduct(mDirection, Vector2Subtract(mPosition, b->mPosition)) > 0) {
					b->Die();					
				}else
				{
					boidIndex ++;

				}
				count++;
			}
			if(count > 5) break;
		}

	}


	if (count != 0)
	{
		positionTotal = Vector2{ positionTotal.x / count, positionTotal.y / count };
	}

	return Vector2Normalize(positionTotal);
}

bool Boids::IsCollidingAabb(Rectangle obstacle, float margin)
{
	return mPosition.x < (obstacle.x + margin + obstacle.width)
	&& (mPosition.x + mSize) > (obstacle.x - margin)
	&& mPosition.y < (obstacle.y + margin + obstacle.height)
	&& (mPosition.y + mSize) > (obstacle.y- margin);
}

void Boids::Die()
{
	mIsAlive = false;
}





