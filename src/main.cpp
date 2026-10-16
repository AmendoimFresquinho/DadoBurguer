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

    Texture2D fundo = LoadTexture("DadoBurguer/assets/Fundo.png");

    ESTADO_PROGRAMA EstadoPrograma = MENU; 
    std::vector<Rectangle> paredes;
    std::vector<Bloco> blocos;
    ConstruirMapa(paredes, blocos);
    AnimJogador animJogador = CriarAnimJogador("DadoBurguer/assets/jogador.png");
    TelaFogao telaFogao = CriarTelaFogao(LARGURA, ALTURA);
    EstadoJogo estado = { false, "", 0.0f, TELA_JOGO };
    std::vector<Rectangle> solidos = paredes;
    
    for (size_t i = 0; i < blocos.size(); i++) 
        solidos.push_back(blocos[i].rect);

    Jogador jogador = { 250.0f, 64.0f, { 400, 360 }, { 0, 0 }, 32.0f, 64.0f };

    Rectangle btnIniciar = { POS_X, POS_Y_INICIAL + (0 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnDificuldade = { POS_X, POS_Y_INICIAL + (1 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnComoJogar = { POS_X, POS_Y_INICIAL + (2 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnHistorico = { POS_X, POS_Y_INICIAL + (3 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnSair = { POS_X, POS_Y_INICIAL + (4 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };

    while (!WindowShouldClose()) {

        BeginDrawing();

        float dt = GetFrameTime();

        switch(EstadoPrograma){

        case JOGANDO: { //Caso o jogador esteja jogando
            SetExitKey(0);

            if(IsKeyPressed(KEY_ESCAPE)) 
                EstadoPrograma = PAUSADO;

            Movimentacao(jogador);
            Colisoes(jogador, dt, solidos);
            Vector2 antes = jogador.posicao;

            Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH);

            switch (estado.tela) { // SWITCH CASE DE LOGICA
            
                case TELA_JOGO:
                    Movimentacao(jogador);
                    Colisoes(jogador, dt, solidos);
                    AtualizarAnimJogador(animJogador, Vector2Subtract(jogador.posicao, antes), dt);
                    alvo = ProcuraInteragir(jogador, blocos, REACH);
                    if (alvo != nullptr && IsKeyPressed(KEY_E)) 
                        FazInteracao(*alvo, estado);
                    break;
                
                case TELA_FOGAO:
                    if (AtualizarTelaFogao(telaFogao)) 
                        estado.tela = TELA_JOGO;
                    break;
            }   

            ClearBackground(RAYWHITE);

            DrawRectangle(32, 32, 585, 656, Color{ 235, 225, 210, 255 });
            DrawRectangle(629, 32, 619, 656, Color{ 210, 225, 235, 255 });

            for (size_t i = 0; i < paredes.size(); i++) DrawRectangleRec(paredes[i], GRAY);
            for (size_t i = 0; i < blocos.size(); i++)  DesenharBloco(blocos[i]);

            Rectangle hb = HitBox(jogador);
            Rectangle sprite = { jogador.posicao.x - jogador.tamanho / 2, (jogador.posicao.y + jogador.alturaHit / 2) - jogador.tamanho, jogador.tamanho, jogador.tamanho };

            if (alvo != nullptr) {
                DrawText(TextFormat("[E] %s", alvo->nome.c_str()), (int)hb.x - 10, (int)hb.y - 24, 20, BLACK);
            }

            switch (estado.tela) { // SWITCH CASE DE GRAFICOS
                case TELA_JOGO:
                    DesenharAnimJogador(animJogador, sprite); 
                break;                                   
                case TELA_FOGAO:
                    DesenharTelaFogao(telaFogao);
                break;
            }   
        break;
        }

        case MENU:{ // Caso o jogador esteja no menu

            SetExitKey(0);

            ClearBackground(BLACK); // 1º Limpa a tela
            DrawTexture(fundo, 0, 0, WHITE);

            if(CheckCollisionPointRec(GetMousePosition(), btnIniciar)) {
                DrawRectangleRounded(btnIniciar, 0.4f, 4, Fade(GREEN, 0.15f));
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    EstadoPrograma = JOGANDO;
            } if(CheckCollisionPointRec(GetMousePosition(), btnHistorico)) {
                DrawRectangleRounded(btnHistorico, 0.4f, 4, Fade(GREEN, 0.15f));
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    EstadoPrograma = HISTORICO;
            } if(CheckCollisionPointRec(GetMousePosition(), btnDificuldade)) {
                DrawRectangleRounded(btnDificuldade, 0.4f, 4, Fade(YELLOW, 0.15f));
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    EstadoPrograma = DIFICULDADE;
            } if(CheckCollisionPointRec(GetMousePosition(), btnSair)) {
                DrawRectangleRounded(btnSair, 0.4f, 4, Fade(GREEN, 0.15f));
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    WindowShouldClose();
            } if(CheckCollisionPointRec(GetMousePosition(), btnComoJogar)) {
                DrawRectangleRounded(btnComoJogar, 0.4f, 4, Fade(YELLOW, 0.15f));
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    EstadoPrograma = COMO_JOGAR;
            }
            
        break;
        }

        case PAUSADO: {

            SetExitKey(0);
            ClearBackground(BLACK);
            DrawText("PAUSADO", LARGURA / 2, ALTURA / 2, 100, RED);
            if(IsKeyPressed(KEY_ESCAPE))
                EstadoPrograma = JOGANDO;
            
            break;
        }
        }
    
    EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) UnloadTexture(blocos[i].textura);

    DescarregarAnimJogador(animJogador);
    UnloadTexture(fundo);
    CloseWindow();
    return 0;
}
