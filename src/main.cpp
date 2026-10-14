#include "raylib.h"
#include "imagens.hpp"
#include "ingredientes.hpp"


int main(){
    InitWindow(500, 500, "Títuloso");
    SetTargetFPS(60);

    Imagens::Ingredientes imagem_topo {Geral::Ingredientes::PAO_SUPERIOR, "assets/topo.png", 0, 0};

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawTexture(imagem_topo.textura, 100, 100, WHITE);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}