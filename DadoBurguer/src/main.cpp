#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>

int main() {
    
    InitWindow((int)LARGURA, (int)ALTURA, "DADOBURGUER");
    SetTargetFPS(60);

    Texture2D paoCima = LoadTexture("DadoBurguer/assets/INV/cima_pao_inventario.png");
    Texture2D paoBaixo = LoadTexture("DadoBurguer/assets/INV/baixo_pao_inventario.png");
    Texture2D cheddar = LoadTexture("DadoBurguer/assets/INV/cheddar_inventario.png");
    Texture2D suico = LoadTexture("DadoBurguer/assets/INV/suico_inventario.png");
    Texture2D carne_crua = LoadTexture("DadoBurguer/assets/INV/carne_crua_inventario.png");
    Texture2D alface = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D tomate = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D ketchup = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D mostarda = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D cebola = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D ovo = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D bacon = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D picles = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D carne_assada = LoadTexture("DadoBurguer/assets/INV/carne_assada_inventario.png");
    Texture2D mouse = LoadTexture("DadoBurguer/assets/mouse.png");

    Rectangle mouseRect = {0.0f, 0.0f, (float) mouse.width, (float) mouse.height};
    float mouseLarg, mouseEscala;
    Rectangle mouseDestRect;

    IngredienteJogo Pao_cima = { 'z', false, paoCima, "Pao de Cima", 0 };
    IngredienteJogo Pao_baixo ={ 'x', false, paoBaixo, "Pao de Baixo", 0 };
    IngredienteJogo Carne = { 'n', true, carne_crua, "Carne", VALIDADE };
    IngredienteJogo Queijo_Suico = { 's', true, suico, "Suico", VALIDADE };
    IngredienteJogo Cheddar = { 'q', true, cheddar, "Cheddar", VALIDADE };
    IngredienteJogo Alface = { 'a', false, alface, "Alface", 0};
    IngredienteJogo Ketchup = { 'k', false, ketchup, "Ketchup", 0};
    IngredienteJogo Mostarda = { 'm', false, mostarda, "Mostarda", 0};
    IngredienteJogo Picles = { 'p', false, picles, "Picles", 0};
    IngredienteJogo Cebola = { 'c', false, cebola, "Cebola", 0};
    IngredienteJogo Tomate = { 't', false, tomate, "Tomate", 0};
    IngredienteJogo Ovo = { 'o', false, ovo, "Ovo", 0};
    IngredienteJogo Bacon = { 'b', false, bacon, "Bacon", 0};
    IngredienteJogo Carne_Assada = {'k', true, carne_assada, "Carne Assada"};

    Texture2D menu = LoadTexture("DadoBurguer/assets/Menu.png");
    Texture2D pausa = LoadTexture("DadoBurguer/assets/pausa.png");
    Texture2D fundo = LoadTexture("DadoBurguer/assets/fundo.png");

    ESTADO_PROGRAMA EstadoPrograma = MENU; 
    std::vector<Rectangle> paredes;
    std::vector<Bloco> blocos;
    
    ConstruirMapa(paredes, blocos);
    AnimJogador animJogador = CriarAnimJogador("DadoBurguer/assets/jogador.png");
    TelaFogao telaFogao = CriarTelaFogao(LARGURA, ALTURA);
    TelaEstoque telaEstoque = CriarTelaEstoque(LARGURA, ALTURA, Pao_cima, Pao_baixo, Carne, Queijo_Suico, Ovo, Bacon, Mostarda, Ketchup, Alface, Tomate, Cebola, Cheddar, Picles);
    TelaInventario telaInventario = CriarTelaInventario(LARGURA, ALTURA);

    EstadoJogo estado = { false, TELA_JOGO };
    std::vector<Rectangle> solidos = paredes;
    
    FilaPrioridade HEAP_PERECIVEIS;
    HEAP_PERECIVEIS.tamanho = 0;

    ListaContiguaINV Inventario;
    Inventario.tamanho = 0;
    int Turno = 0;
    int Stamina = STAMINA;

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
        HideCursor();
        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH); // Sempre procura um bloco possivelmente interagivel
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();

        float dt = GetFrameTime();

        switch(EstadoPrograma){

            case JOGANDO: { //Caso o jogador esteja jogando

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                //HideCursor();

                if(IsKeyPressed(KEY_ESCAPE)) 
                    EstadoPrograma = PAUSADO;
                if(Stamina <= 0)
                    passaTurno(Turno, Stamina);
                    
                Vector2 antes = jogador.posicao;

                switch (estado.tela) { // SWITCH CASE DE LOGICA
                
                    case TELA_JOGO:
                        Movimentacao(jogador);
                        Colisoes(jogador, dt, solidos);
                        AtualizarAnimJogador(animJogador, Vector2Subtract(jogador.posicao, antes), dt);
                        if (alvo != nullptr && IsKeyPressed(KEY_E) && testaStamina(Stamina, alvo->staminaGasta) >= 0){
                            FazInteracao(*alvo, estado);
                            gastaStamina(Stamina, alvo->staminaGasta);
                        } 
                        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_I)) estado.tela = TELA_INVENTARIO;
                        break;
                    case TELA_FOGAO:
                        if (AtualizarTelaFogao(telaFogao)) 
                        estado.tela = TELA_JOGO;
                        break;
                    case TELA_ESTOQUE:
                        char escolhidoEST;
                        int escolhidoINV;
                        if (AtualizarTelaEstoque(telaEstoque, escolhidoEST, escolhidoINV)){ estado.tela = TELA_JOGO; }
                        if(escolhidoEST != '\0') {
                            adicionaNoInventario(escolhidoEST, Inventario, Pao_cima, Pao_baixo, Carne, Queijo_Suico, Ovo, Bacon, Mostarda, Ketchup, Alface, Tomate, Cebola, Cheddar, Picles); 
                            colocaNoHeapEstragado(enderecoDe(Inventario, Inventario.tamanho - 1), HEAP_PERECIVEIS, Turno);
                            fpImprimir(HEAP_PERECIVEIS);
                        }
                        if(escolhidoINV != -1) {
                            removeDoInventario(escolhidoINV, Inventario); 
                            reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            imprime(Inventario);
                            fpImprimir(HEAP_PERECIVEIS);
                        }
                        break;
                    case TELA_INVENTARIO:
                        int clicado;
                        if (AtualizarTelaInventario(telaInventario, clicado)) estado.tela = TELA_JOGO;        
                        break;  
                }   

                switch (estado.tela) { // SWITCH CASE DE GRAFICOS

                    case TELA_JOGO:
                        DesenharMundo(fundo, blocos, jogador, animJogador, alvo, estado, Turno, Stamina);   // EM_JOGO
                        BotaoPassaTurno(Turno, Stamina);
                    break;              

                    case TELA_FOGAO:
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaFogao(telaFogao, Inventario);
                        break;

                    case TELA_ESTOQUE: 
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaEstoque(telaEstoque, Inventario);
                        break;
                    
                    case TELA_INVENTARIO: 
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaInventario(telaInventario, Inventario);
                        break;
                    
                }   
                break; //BREAK DO CASE GRANDE, NAO TIRAR (PARA MY PLISNO ASS)
            }

            case MENU: { // Caso o jogador esteja no menu

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                //ShowCursor();

                ClearBackground(WHITE); 
                DrawTexture(menu, 0, 0, WHITE);

                if(CheckCollisionPointRec(GetMousePosition(), btnIniciar)) {
                    DrawRectangleRounded(btnIniciar, 0.35f, 8, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador, Inventario, Turno, Stamina);
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
                        FechaJogo(animJogador, telaEstoque, menu, pausa, fundo, paoCima, paoBaixo, cheddar, suico, carne_crua, alface, tomate, ketchup, mostarda, cebola, ovo, bacon, picles);
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

                //ShowCursor();
                DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);   // PAUSADO
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
                        ReiniciarJogo(jogador, estado, animJogador, Inventario, Turno, Stamina);
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

    mouseEscala = ((float)(((int)(GetTime() * 100) % 120)+1) / 60);          // Gera de 1/60 até 2
    mouseEscala = (mouseEscala > 1.0f)? 2.0f - mouseEscala : mouseEscala;
    mouseLarg = (mouse.width) * mouseEscala;
    mouseDestRect = {mousePos.x - (mouseLarg/2), mousePos.y - (mouse.height/2), mouseLarg, (float) mouse.height};
    DrawTexturePro(mouse, mouseRect, mouseDestRect, (Vector2) {0.0f, 0.0f}, 0.0f, WHITE);
    EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) 
            UnloadTexture(blocos[i].textura);

    DescarregarAnimJogador(animJogador);
    DescarregarTelaEstoque(telaEstoque);
    UnloadTexture(menu);
    UnloadTexture(pausa);
    UnloadTexture(fundo);
    UnloadTexture(pausa);
    UnloadTexture(paoCima);
    UnloadTexture(paoBaixo);
    UnloadTexture(cheddar);
    UnloadTexture(suico);
    UnloadTexture(carne_crua);
    UnloadTexture(alface);
    UnloadTexture(tomate);
    UnloadTexture(ketchup);
    UnloadTexture(mostarda);
    UnloadTexture(cebola);
    UnloadTexture(ovo);
    UnloadTexture(bacon);
    UnloadTexture(picles);
    UnloadTexture(mouse);

    CloseWindow();

    return 0;
}