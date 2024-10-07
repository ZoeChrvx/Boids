#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "Obstacles.h"

class Boids

{
public:
	Boids();
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


private:
	int boidEquip;
	int boidEnemyEquip;
	float boidSize;
	int boidID;
	Color boidColor;
	float minimumDistance;
	float maxPerceiveDistance;
	float cohesionRadius;
	float speed = 150;
	Vector2 direction = Vector2One();
	Vector2 boidPosition = Vector2{0,0 };
	Texture2D boidTexture;
};

