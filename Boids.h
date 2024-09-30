#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"

class Boids

{
public:
	Boids();
	Boids(float x, float y, float size, Color color);
	~Boids();
	void SetPosition(float x, float y);
	void Move(Vector2 move);
	void Draw();
	void Detection();


private:
	float boidX;
	float boidY;
	float boidSize;
	Color boidColor; 

	Vector2 direction;
	Vector2 boidPosition = Vector2{ boidX, boidY };
};

