#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include "Obstacles.h"

class Boids

{
public:
	Boids();
	Boids(float x, float y, float size, int id, Color color);
	~Boids();
	void SetPosition(float x, float y);
	void Move(Vector2 move);
	void Draw();
	int GetID();

	Vector2 Detection(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList);
	void Update(std::vector<Boids*> &boidList, std::vector<Obstacles*> &obstList);
	Vector2 Aligment(std::vector<Boids*>& boidList);


private:
	float boidSize;
	int boidID;
	Color boidColor;
	float minimumDistance;
	float maxPerceiveDistance;
	float speed = 150;
	Vector2 direction = Vector2One();
	Vector2 boidPosition = Vector2{0,0 };
};

