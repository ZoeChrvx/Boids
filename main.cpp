#include "raylib.h"
#include "Boids.h"
#include "Obstacles.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    InitWindow(1920, 1080, "My first Raylib window!");
    Texture2D fishTexture = LoadTexture("resources/WhiteFish.png");
    SetTargetFPS(60);
    vector<Boids*> boids;
    for (int i = 0; i < 800; i++) {
        int randX;
        int randY;
        int randEquip = GetRandomValue(1, 3);
        int enemyEquip = 0;
        if (randEquip == 1) {
            randX = GetRandomValue(20, 600);
            randY = GetRandomValue(20, 200);
            enemyEquip == 2;
        }
        else if (randEquip == 2) {
            randX = GetRandomValue(620, 1200);
            randY = GetRandomValue(220, 400);
            enemyEquip == 3;
        }
        else {
            randX = GetRandomValue(1220, 1880);
             randY = GetRandomValue(420, 1040);
            enemyEquip == 1;
        }

        
        boids.push_back(new Boids(randX, randY, 10, i, randEquip, enemyEquip, DARKPURPLE, fishTexture));
    }
    vector<Obstacles*> obstacles;
    obstacles.push_back(new Obstacles({ 300, 150, 100, 300 }, BROWN));
    obstacles.push_back(new Obstacles({ 1200,600,200,200 }, BROWN));
    obstacles.push_back(new Obstacles({ 1900,0,20,1080 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,1060,1920,20 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,0,20,1080 }, BROWN));
    obstacles.push_back(new Obstacles({ 0,0,1920,20 }, BROWN));

    

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
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