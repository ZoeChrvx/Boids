#include "raylib.h"
#include "Boids.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    InitWindow(800, 800, "My first Raylib window!");
    SetTargetFPS(60);
    vector<Boids*> boids;
    for (int i = 0; i < 50; i++) {
        int randX = GetRandomValue(20, 780);
        int randY = GetRandomValue(20, 780);
        
        boids.push_back(new Boids(randX, randY, 10, i, LIGHTGRAY));

    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        for (Boids* b : boids) {
            b->Update(boids);  
            
        }

        for (Boids* b : boids) {
            b->Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}