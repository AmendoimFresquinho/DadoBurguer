#include "raylib.h"

int main(){
    InitWindow(500, 500, "Títuloso");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}