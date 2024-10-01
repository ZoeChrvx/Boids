#include "raylib.h"
#include "Boids.h"
#include "Obstacles.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    InitWindow(1920, 1080, "My first Raylib window!");
    SetTargetFPS(60);
    vector<Boids*> boids;
    for (int i = 0; i < 500; i++) {
        int randX = GetRandomValue(20, 1880);
        int randY = GetRandomValue(20, 1040);
        
        boids.push_back(new Boids(randX, randY, 5, i, DARKPURPLE));
    }
    vector<Obstacles*> obstacles;
    obstacles.push_back(new Obstacles({ 300, 150, 200, 500 }, BROWN));
    obstacles.push_back(new Obstacles({ 1200,600,400,400 }, BROWN));
    obstacles.push_back(new Obstacles({ 1900,0,20,1080 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,1060,1920,20 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,0,20,1080 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,0,1920,20 }, BROWN));


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        for (Boids* b : boids) {
            b->Update(boids, obstacles);  
        }

        for (Boids* b : boids) {
            b->Draw();
        }
        for (Obstacles* o : obstacles) {
            o->Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}