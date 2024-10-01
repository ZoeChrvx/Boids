#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"

class Boids

{
public:
	Boids();
	Boids(float x, float y, float size, int id, Color color);
	~Boids();
	void SetPosition(float x, float y);
	void Move(Vector2 move);
	void Draw();
	Vector2 Detection(std::vector<Boids*>& boidList);
	int getID();
	void Update(std::vector<Boids*> &boidList);


private:
	float boidSize;
	int boidID;
	Color boidColor;
	float minimumDistance = 30;
	Vector2 direction = Vector2One();
	float speed = 150;
	Vector2 boidPosition = Vector2{0,0 };
};

