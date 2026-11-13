#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include <string>
#include "Constantes.hpp"
#include <random>

Cliente criaClientePadrao(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, int &codigoMax, int &codigoMin){

    Cliente novo;

    novo.ehEspecial = false;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> Skin(1, 10);

    int SkinCliente = Skin(gen);

    switch (SkinCliente) {
    case 1:
        novo.sprite = sprites[0];
        break;
    case 2:
        novo.sprite = sprites[1];
        break;
    case 3:
        novo.sprite = sprites[2];
        break;
    case 4:
        novo.sprite = sprites[3];
        break;
    case 5:
        novo.sprite = sprites[4];
        break;
    case 6:
        novo.sprite = sprites[5];
        break;
    case 7:
        novo.sprite = sprites[6];
        break;
    case 8:
        novo.sprite = sprites[7];
        break;
    case 9:
        novo.sprite = sprites[8];
        break;
    case 10:
        novo.sprite = sprites[9];       
        break;

    default: break;
    }

    if(dificuldade == FACIL){
        std::uniform_int_distribution<> facil(8, 10);
        novo.Paciencia = facil(gen);
    }
    if(dificuldade == MEDIO){
        std::uniform_int_distribution<> medio(6, 8);
        novo.Paciencia = medio(gen);
    }
    if(dificuldade == DIFICIL){
        std::uniform_int_distribution<> dificil(4, 6);
        novo.Paciencia = dificil(gen);
    }
    if(dificuldade == IMPOSSIVEL){
        std::uniform_int_distribution<> impossivel(2, 4);
        novo.Paciencia = impossivel(gen);
    }

    novo.pedido = SorteiaPedidos(raiz, codigoMax, codigoMin, hash, HIT, MISS);

    return novo;

}

Cliente CriaclienteEspecial(Texture2D sprites[2]){
    
    Cliente novo;

    novo.ehEspecial = true;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> qualEh(1, 2);

    int ESCOLHIDO = qualEh(gen);

    switch (ESCOLHIDO) {
    case 1:
        novo.sprite = sprites[0];
        novo.pedido = "xqsqsqsqsz";
        novo.Paciencia = 1;
        break;
    case 2:
        novo.sprite = sprites[1];
        novo.pedido = "xkaqnxapnz"; //BIG MAC
        novo.Paciencia = 5;
        break;
    default: break;
    }

    return novo;
}

void criaFilaClientes(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, Texture2D Especiais[2], FilaEnc &Clientes, int &TAM_FILA, int &codigoMax, int &codigoMin){

    if(dificuldade == FACIL) TAM_FILA = TAMANHO_FILA_FACIL;
    else if(dificuldade == MEDIO) TAM_FILA = TAMANHO_FILA_MEDIO;
    else if(dificuldade == DIFICIL) TAM_FILA = TAMANHO_FILA_DIFICIL;
    else TAM_FILA = TAMANHO_FILA_IMPOSSIVEL;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> Especial(1, 10);

    int EhEspecial;

    for(int i = 0; i < 9; i++){   

        EhEspecial = Especial(gen);

        if(EhEspecial >= 0 && EhEspecial <= 9){
            Cliente novo = criaClientePadrao(dificuldade, sprites, raiz, hash, HIT, MISS, codigoMax, codigoMin);
            enfileira(Clientes, novo);
        }
        else {
            Cliente novo = CriaclienteEspecial(Especiais);
            enfileira(Clientes, novo);
        }
    }
}

void desenhaFila(FilaEnc &f){

    NodoFila *aux = f.frente;
    Vector2 Posicao = {680, 280};

    while(aux != nullptr){
        if(aux->dado.ehEspecial){
            SetTextureFilter(aux->dado.sprite, TEXTURE_FILTER_POINT);
            DrawTextureEx(aux->dado.sprite, Posicao, 0.0f, 1.0f, WHITE);
        }
        else{
            SetTextureFilter(aux->dado.sprite, TEXTURE_FILTER_POINT);
            DrawTextureEx(aux->dado.sprite, Posicao, 0.0f, 2.0f, WHITE);
        }
        aux = aux->prox;
        Posicao.x += 60;
    }
}