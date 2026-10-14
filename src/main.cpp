#include "raylib.h"
#include "imagens.hpp"
#include "ingredientes.hpp"
#include <vector>

int main(){
    InitWindow(500, 500, "Títuloso");
    SetTargetFPS(60);

    Imagens::TxtPack_Ingredientes pacote;
    pacote.reserve(10);

    Imagens::carregarTextura(pacote, "assets/bife.png", Geral::Ingredientes::CARNE, 0, 2.5);
    Imagens::carregarTextura(pacote, "assets/pao.png", Geral::Ingredientes::PAO_INFERIOR, 0, 4);
    Imagens::carregarTextura(pacote, "assets/topo.png", Geral::Ingredientes::PAO_SUPERIOR, 4.5, 10);
    Imagens::carregarTextura(pacote, "assets/ketchup.png", Geral::Ingredientes::KETCHUP, 0, 0.5);
    Imagens::carregarTextura(pacote, "assets/cheddar.png", Geral::Ingredientes::QUEIJO_CHEDDAR, 0.6, 0.6);
    Geral::Hamburguer burgui {};
    burgui.empilharIngrediente(Geral::Ingredientes::PAO_INFERIOR);
    burgui.empilharIngrediente(Geral::Ingredientes::CARNE);
    burgui.empilharIngrediente(Geral::Ingredientes::KETCHUP);
    burgui.empilharIngrediente(Geral::Ingredientes::QUEIJO_CHEDDAR);
    burgui.empilharIngrediente(Geral::Ingredientes::PAO_SUPERIOR);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGRAY);

        Imagens::desenharHamburguer(burgui, 100, 100, pacote);

        /*DrawTexture(pacote[0].textura, 100, 100, WHITE);
        DrawTexture(pacote[1].textura, 150, 100, WHITE);
        DrawTexture(pacote[2].textura, 200, 100, WHITE);*/


        EndDrawing();
    }

    Imagens::descarregarPacote(pacote);
    CloseWindow();
    return 0;
}