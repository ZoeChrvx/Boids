#include "raylib.h"
#include "Boids.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    
    cout << "Hello World" << endl;

    InitWindow(300, 300, "My first Raylib window!");
    SetTargetFPS(60);
    vector<Boids*> boids;
    for (int i = 0; i < 5; i++) {
        int randX = GetRandomValue(20, 280);
        int randY = GetRandomValue(20, 280);
        boids.push_back(new Boids(randX, randY / 2, 2, LIGHTGRAY));
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        for (Boids* b : boids) {
            Vector2 speedMovement{1,1};
            b->Move(speedMovement);
            
            if (b->boidPosition.x >= 280) {
                speedMovement.x = -speedMovement.x;
            }
            if (b->boidPosition.y <= 20) {
                speedMovement.y = -speedMovement.y;
            }
        }

        for (Boids* b : boids) {
            b->Draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}