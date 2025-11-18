#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "Obstacles.h"

class Boids

{
public:
	Boids(float x, float y, float size, int id, int equip, int enemyEquip, Color color, Texture2D texture);
	~Boids();

	void SetPosition(float x, float y);
	void Move(Vector2 move);
	void Draw();
	int GetID();
	int GetEquip();
	void SetColor(Color color);

	void Update(std::vector<Boids*> &boidList, std::vector<Obstacles*> &obstList);

	Vector2 Aligment(std::vector<Boids*>& boidList);
	Vector2 Group(std::vector<Boids*>& boidList);
	Vector2 Avoid(std::vector<Boids*>& boidList);
	Vector2 AvoidObstacles(std::vector<Obstacles*>& obstacleList);
	Vector2 AvoidMouse();
	Vector2 AvoidPredator(std::vector<Boids*>& boidList);
	Vector2 Attack(std::vector<Boids*>& boidList);
	bool IsCollidingAabb(Rectangle obstacle, float margin = 5.0f);
	void Die();

	bool mIsAlive;

private:
	int mTeam;
	int mEnemyTeam;
	float mSize;
	int mID;
	Color mColor;
	float minimumDistance;
	float maxPerceiveDistance;
	float cohesionRadius;
	float mSpeed;
	Vector2 mDirection;
	float mTurnSpeed;
	Vector2 mPosition;
	Texture2D mTexture;
};

