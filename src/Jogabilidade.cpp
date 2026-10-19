#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>

void passaTurno(int &turno, int &stamina){
    turno++;
    stamina = STAMINA;
}

void desenhaTurno(const int &turno, const int &stamina){
    int distancia = 0;
    DrawText("Turno:", 5, 5, 20, BLACK);
    DrawText(TextFormat("%d", turno), MeasureText("Turno", 20) + 15, 5, 20, RED);
    DrawText("STAMINA:", 5, ALTURA - 25, 20, BLACK);
    for(int i = 0; i < stamina; i++){
        Rectangle STAM = {5.0f + distancia + MeasureText("STAMINA:", 22), ALTURA - 23, 30, 15};
        DrawRectangleRounded(STAM, 2, 4, LIGHTGRAY);
        distancia += 40;
    }
}

void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &menu, Texture2D &pausa, Texture2D &fundo, Texture2D &paoCima, Texture2D &paoBaixo,Texture2D &cheddar,Texture2D &suico, Texture2D &carne_crua, Texture2D &alface, Texture2D &tomate, Texture2D &ketchup, Texture2D &mostarda, Texture2D &cebola, Texture2D &ovo, Texture2D &bacon, Texture2D &picles){

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

    CloseWindow();
}

void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina) {
    jogador = { 250.0f, 64.0f, { 340, 360 }, { 0, 0 }, 32.0f, 64.0f };
    estado = { false, TELA_JOGO };
    anim.frame = 0;
    anim.tempo = 0.0f;
    anim.direcao = DIR_BAIXO;
    inv.tamanho = 0;
    stamina =  STAMINA;
    turno = 0;
}