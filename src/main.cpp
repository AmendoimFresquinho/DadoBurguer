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

    // Sólidos = paredes + todos os blocos
    std::vector<Rectangle> solidos = paredes;
    for (size_t i = 0; i < blocos.size(); i++) solidos.push_back(blocos[i].rect);

    EstadoJogo estado = { false, "", 0.0f };
    Jogador jogador = { 250.0f, 32.0f, { 400, 360 }, { 0, 0 } };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        Movimentacao(jogador);
        Colisoes(jogador, dt, solidos);

        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH);
        if (alvo != nullptr && IsKeyPressed(KEY_E)) FazInteracao(*alvo, estado);
        if (estado.tempoMensagem > 0.0f) estado.tempoMensagem -= dt;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Pisos (cozinha à esquerda, clientes à direita)
        DrawRectangle(32, 32, 585, 656, Color{ 235, 225, 210, 255 });
        DrawRectangle(629, 32, 619, 656, Color{ 210, 225, 235, 255 });

        for (size_t i = 0; i < paredes.size(); i++) DrawRectangleRec(paredes[i], GRAY);
        for (size_t i = 0; i < blocos.size(); i++)  DesenharBloco(blocos[i]);

        Rectangle hb = HitBox(jogador);
        DrawRectangleRec(hb, MAROON);

        if (alvo != nullptr) {
            DrawText(TextFormat("[E] %s", alvo->nome.c_str()), (int)hb.x - 10, (int)hb.y - 24, 20, BLACK);
        }

        // Barra de status na parede do topo
        if (estado.tempoMensagem > 0.0f) DrawText(estado.mensagem, 44, 6, 20, WHITE);
        DrawText(estado.fogaoLigado ? "Fogao: LIGADO" : "Fogao: desligado",
                 (int)LARGURA - 220, 6, 20, WHITE);

        EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) UnloadTexture(blocos[i].textura);
    CloseWindow();
    return 0;
}
