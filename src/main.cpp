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
    TelaEstoque telaEstoque = CriarTelaEstoque(LARGURA, ALTURA);
    EstadoJogo estado = { false, TELA_JOGO };
    std::vector<Rectangle> solidos = paredes;
    
    for (size_t i = 0; i < blocos.size(); i++) 
        solidos.push_back(blocos[i].rect);

    Jogador jogador = { 250.0f, 64.0f, { 350, 360 }, { 0, 0 }, 32.0f, 64.0f };

    Rectangle btnIniciar = { POS_X, POS_Y_INICIAL + (0 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO }; // Menu
    Rectangle btnDificuldade = { POS_X, POS_Y_INICIAL + (1 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnComoJogar = { POS_X, POS_Y_INICIAL + (2 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnHistorico = { POS_X, POS_Y_INICIAL + (3 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnSair = { POS_X, POS_Y_INICIAL + (4 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };

    Rectangle pausaVoltar = { 480, 268, 320, 76 }; // Pausa
    Rectangle pausaReiniciar = { 480, 366, 320, 76 };
    Rectangle pausaMenu = { 480, 464, 320, 76 };

    while (!WindowShouldClose()) {

        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH); // Sempre procura um bloco possivelmente interagivel

        BeginDrawing();

        float dt = GetFrameTime();

        switch(EstadoPrograma){

            case JOGANDO: { //Caso o jogador esteja jogando

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                HideCursor();

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
                    case TELA_ESTOQUE:
                        char escolhido;
                        if (AtualizarTelaEstoque(telaEstoque, escolhido)) estado.tela = TELA_JOGO;
                        break;
                }   

                switch (estado.tela) { // SWITCH CASE DE GRAFICOS

                    case TELA_JOGO:
                        DesenharMundo(fundo, blocos, jogador, animJogador, alvo, estado);   // EM_JOGO             
                    break;              

                    case TELA_FOGAO:
                        ShowCursor();
                        DrawTexture(fundo, 0, 0, WHITE);
                         for (size_t i = 0; i < blocos.size(); i++)      
                            DesenharBloco(blocos[i]); // Isso deixa o fundo escuro
                        DesenharTelaFogao(telaFogao);
                        break;

                    case TELA_ESTOQUE: {
                        ShowCursor();
                        DrawTexture(fundo, 0, 0, WHITE);
                         for (size_t i = 0; i < blocos.size(); i++)      
                            DesenharBloco(blocos[i]);  // Isso deixa o fundo escuro
                        DesenharTelaEstoque(telaEstoque);
                        break;
                    }            
                }   
                break; //BREAK DO CASE GRANDE, NAO TIRAR (PARA MY PLISNO ASS)
            }

            case MENU: { // Caso o jogador esteja no menu

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                ShowCursor();

                ClearBackground(WHITE); 
                DrawTexture(menu, 0, 0, WHITE);

                if(CheckCollisionPointRec(GetMousePosition(), btnIniciar)) {
                    DrawRectangleRounded(btnIniciar, 0.35f, 8, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador);
                        EstadoPrograma = JOGANDO;
                    }
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnHistorico)) {
                    DrawRectangleRounded(btnHistorico, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = HISTORICO;
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnDificuldade)) {
                    DrawRectangleRounded(btnDificuldade, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = DIFICULDADE;
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnSair)) {
                    DrawRectangleRounded(btnSair, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        CloseWindow();
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnComoJogar)) {
                    DrawRectangleRounded(btnComoJogar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = COMO_JOGAR;
                }
                break;
            }

            case PAUSADO: { // Caso o jogador tenha pausado

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                if(IsKeyPressed(KEY_ESCAPE)) 
                    EstadoPrograma = JOGANDO;

                ShowCursor();
                DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado);   // PAUSADO
                DrawRectangle(0, 0, LARGURA, ALTURA, Color{ 0, 0, 0, 167 });   // película preta translúcida
                DrawTexture(pausa, 420, 140, WHITE);

                if(CheckCollisionPointRec(GetMousePosition(), pausaVoltar)) {
                    DrawRectangleRounded(pausaVoltar, 0.4f, 4, ColorAlpha(LIGHTGRAY, 0.5f));
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

            case HISTORICO: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
            }

            case DIFICULDADE: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
            }

            case COMO_JOGAR: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
            }
        }
    EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) 
            UnloadTexture(blocos[i].textura);

    DescarregarAnimJogador(animJogador);
    DescarregarTelaEstoque(telaEstoque);
    UnloadTexture(menu);
    UnloadTexture(fundo);
    UnloadTexture(pausa);
    CloseWindow();
    return 0;
}

