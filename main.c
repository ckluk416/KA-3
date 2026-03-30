#include "raylib.h"
#include "fireworks.h"

int main(void) {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Tubes ETS 241524041");
    SetTargetFPS(60);

    Firework fireworksArray[MAX_FIREWORKS] = {0};

    while (!WindowShouldClose()) {
        UpdateFireworks(fireworksArray, MAX_FIREWORKS, screenWidth, screenHeight);

        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawFireworks(fireworksArray, MAX_FIREWORKS);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}