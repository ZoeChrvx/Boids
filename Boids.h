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
	Vector2 Detection(std::vector<Boids*>& boidList, std::vector<Obstacles*>& obstList);
	int getID();
	void Update(std::vector<Boids*> &boidList, std::vector<Obstacles*> &obstList);


private:
	float boidSize;
	int boidID;
	Color boidColor;
	float minimumDistance;
	Vector2 direction = Vector2One();
	float speed = 150;
	Vector2 boidPosition = Vector2{0,0 };
};

