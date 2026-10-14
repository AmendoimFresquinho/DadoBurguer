#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include "imagens.hpp"
#include "ingredientes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>

int main() {
    InitWindow((int)LARGURA, (int)ALTURA, "Cozinha");
    SetTargetFPS(60);

    std::vector<Rectangle> paredes;
    std::vector<Bloco> blocos;
    ConstruirMapa(paredes, blocos);

    TelaFogao telaFogao = CriarTelaFogao(LARGURA, ALTURA);
    EstadoJogo estado = { false, "", 0.0f, TELA_JOGO };

    std::vector<Rectangle> solidos = paredes;
    for (size_t i = 0; i < blocos.size(); i++) solidos.push_back(blocos[i].rect);

    Jogador jogador = { 250.0f, 32.0f, { 400, 360 }, { 0, 0 } };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        Movimentacao(jogador);
        Colisoes(jogador, dt, solidos);

        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH);

        switch (estado.tela) { // SWITCH CASE DE LOGICA
            
            case TELA_JOGO:
                Movimentacao(jogador);
                Colisoes(jogador, dt, solidos);
                alvo = ProcuraInteragir(jogador, blocos, 12.0f);
                if (alvo != nullptr && IsKeyPressed(KEY_E)) 
                    FazInteracao(*alvo, estado);
                break;
            case TELA_FOGAO:
                if (AtualizarTelaFogao(telaFogao)) 
                    estado.tela = TELA_JOGO;
                break;
        }   

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(32, 32, 585, 656, Color{ 235, 225, 210, 255 });
        DrawRectangle(629, 32, 619, 656, Color{ 210, 225, 235, 255 });

        for (size_t i = 0; i < paredes.size(); i++) DrawRectangleRec(paredes[i], GRAY);
        for (size_t i = 0; i < blocos.size(); i++)  DesenharBloco(blocos[i]);

        Rectangle hb = HitBox(jogador);
        DrawRectangleRec(hb, MAROON);

        if (alvo != nullptr) {
            DrawText(TextFormat("[E] %s", alvo->nome.c_str()), (int)hb.x - 10, (int)hb.y - 24, 20, BLACK);
        }

        switch (estado.tela) { // SWITCH CASE DE GRAFICOS
            case TELA_JOGO:
                break;                                   
            case TELA_FOGAO:
                DesenharTelaFogao(telaFogao);
            break;
        }

        EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) UnloadTexture(blocos[i].textura);
    CloseWindow();
    return 0;
}
