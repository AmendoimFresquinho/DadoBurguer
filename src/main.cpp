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
    
    InitWindow((int)LARGURA, (int)ALTURA, "DADOBURGUER");
    SetTargetFPS(60);

    Texture2D menu = LoadTexture("DadoBurguer/assets/Menu.png");
    Texture2D pausa = LoadTexture("DadoBurguer/assets/pausa.png");
    Texture2D fundo = LoadTexture("DadoBurguer/assets/fundo.png");

    ESTADO_PROGRAMA EstadoPrograma = MENU; 
    std::vector<Rectangle> paredes;
    std::vector<Bloco> blocos;
    ConstruirMapa(paredes, blocos);
    AnimJogador animJogador = CriarAnimJogador("DadoBurguer/assets/jogador.png");
    TelaFogao telaFogao = CriarTelaFogao(LARGURA, ALTURA);
    EstadoJogo estado = { false, TELA_JOGO };
    std::vector<Rectangle> solidos = paredes;
    
    for (size_t i = 0; i < blocos.size(); i++) 
        solidos.push_back(blocos[i].rect);

    Jogador jogador = { 250.0f, 64.0f, { 400, 360 }, { 0, 0 }, 32.0f, 64.0f };

    Rectangle btnIniciar = { POS_X, POS_Y_INICIAL + (0 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO }; // Menu
    Rectangle btnDificuldade = { POS_X, POS_Y_INICIAL + (1 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnComoJogar = { POS_X, POS_Y_INICIAL + (2 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnHistorico = { POS_X, POS_Y_INICIAL + (3 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnSair = { POS_X, POS_Y_INICIAL + (4 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };

    Rectangle pausaVoltar = { 480, 268, 320, 76 }; // Pausa
    Rectangle pausaReiniciar = { 480, 366, 320, 76 };
    Rectangle pausaMenu = { 480, 464, 320, 76 };

    while (!WindowShouldClose()) {

        Rectangle hb = HitBox(jogador); // Variaveis dentro do while
        Rectangle sprite = { jogador.posicao.x - jogador.tamanho / 2, (jogador.posicao.y + jogador.alturaHit / 2) - jogador.tamanho, jogador.tamanho, jogador.tamanho };
        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH);

        BeginDrawing();

        float dt = GetFrameTime();

        switch(EstadoPrograma){

            case JOGANDO: { //Caso o jogador esteja jogando

                SetExitKey(KEY_NULL);

                if(IsKeyPressed(KEY_ESCAPE)) 
                    EstadoPrograma = PAUSADO;

                Vector2 antes = jogador.posicao;

                switch (estado.tela) { // SWITCH CASE DE LOGICA
                
                    case TELA_JOGO:
                        Movimentacao(jogador);
                        Colisoes(jogador, dt, solidos);
                        AtualizarAnimJogador(animJogador, Vector2Subtract(jogador.posicao, antes), dt);
                        if (alvo != nullptr && IsKeyPressed(KEY_E)) 
                            FazInteracao(*alvo, estado);
                        break;
                    
                    case TELA_FOGAO:
                        if (AtualizarTelaFogao(telaFogao)) 
                            estado.tela = TELA_JOGO;
                        break;
                }   

                switch (estado.tela) { // SWITCH CASE DE GRAFICOS

                    case TELA_JOGO:
                        DrawTexture(fundo, 0, 0, WHITE);
                        for (size_t i = 0; i < blocos.size(); i++)      
                            DesenharBloco(blocos[i]);
                        if (alvo != nullptr) {
                            DrawText(TextFormat("[E] %s", alvo->nome.c_str()), (int)hb.x - 10, (int)hb.y - 24, 20, BLACK);
                        }
                        DesenharAnimJogador(animJogador, sprite); 
                        break;              

                    case TELA_FOGAO:
                        DrawTexture(fundo, 0, 0, WHITE);
                         for (size_t i = 0; i < blocos.size(); i++)      
                            DesenharBloco(blocos[i]);
                        DesenharTelaFogao(telaFogao);
                        break;
                }   
                break; //BREAK DO CASE GRANDE, NAO TIRAR (PARA MY PLISNO ASS)
            }

            case MENU:{ // Caso o jogador esteja no menu

                SetExitKey(KEY_NULL);

                ClearBackground(WHITE); 
                DrawTexture(menu, 0, 0, Fade(WHITE, 1.0f));

                if(CheckCollisionPointRec(GetMousePosition(), btnIniciar)) {
                    DrawRectangleRounded(btnIniciar, 0.35f, 8, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador);
                        EstadoPrograma = JOGANDO;
                    }
                } if(CheckCollisionPointRec(GetMousePosition(), btnHistorico)) {
                    DrawRectangleRounded(btnHistorico, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = HISTORICO;
                } if(CheckCollisionPointRec(GetMousePosition(), btnDificuldade)) {
                    DrawRectangleRounded(btnDificuldade, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = DIFICULDADE;
                } if(CheckCollisionPointRec(GetMousePosition(), btnSair)) {
                    DrawRectangleRounded(btnSair, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        CloseWindow();
                } if(CheckCollisionPointRec(GetMousePosition(), btnComoJogar)) {
                    DrawRectangleRounded(btnComoJogar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = COMO_JOGAR;
                }
            
                break;
            }

            case PAUSADO: {

                SetExitKey(KEY_NULL);

                DrawTexture(pausa, 420, 140, Color{ 255, 255, 255, 60 });

                 if(CheckCollisionPointRec(GetMousePosition(), pausaVoltar)) {
                    DrawRectangleRounded(pausaVoltar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        EstadoPrograma = JOGANDO;
                    }
                } 
                if(CheckCollisionPointRec(GetMousePosition(), pausaReiniciar)) {
                    DrawRectangleRounded(pausaReiniciar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador);
                        EstadoPrograma = JOGANDO;
                    }
                } 
                if(CheckCollisionPointRec(GetMousePosition(), pausaMenu)) {
                    DrawRectangleRounded(pausaMenu, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = MENU;
                }
                break;
            }
        }
    
    EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) 
            UnloadTexture(blocos[i].textura);

    DescarregarAnimJogador(animJogador);
    UnloadTexture(menu);
    UnloadTexture(fundo);
    CloseWindow();
    return 0;
}
