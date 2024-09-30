#pragma once
#include "raylib.h"
#include <vector>

class Boids

{
public:
	Boids();
	Boids(float x, float y, float size, Color color);
	~Boids();
	void SetPosition(float x, float y);
	void Move(Vector2 move);
	void Draw();

	Vector2 boidPosition = Vector2{ boidX, boidY };
private:
	float boidX;
	float boidY;
	float boidSize;
	Color boidColor;


};

