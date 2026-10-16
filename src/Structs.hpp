#pragma once
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raylib.h"
#include <string>
#include <vector>

struct Produto{
    int cod;
    char nome[50];
    float preco;
};

struct Nodo {
    Nodo *prox;
    Produto dado;
};

struct FilaEnc {
    Nodo *frente;
    Nodo *fim;
};

struct ListaEnc {
    Nodo *ini;
};

struct PilhaEnc {
    Nodo *topo;
};

struct NodoAvl {
    int dado;
    int altura;
    struct NodoAvl *esq;
    struct NodoAvl *dir;
};

enum Acoes {
    SEM_ACAO,
    ABRIR_FOGAO,
    ACAO_ABRIR_GELADEIRA,
    ACAO_ABRIR_ESTOQUE,
    ACAO_CORTAR,
    ACAO_ATENDER
};

enum Tela {
    TELA_JOGO,
    TELA_FOGAO
};

struct EstadoJogo {
    bool fogaoLigado;      
    Tela tela;
};

struct Jogador {
    float velocidade;
    float tamanho;
    Vector2 posicao;
    Vector2 aceleracao;
    float larguraHit;    
    float alturaHit;     
};

struct Bloco {
    Rectangle rect;
    std::string nome;
    Texture2D textura;              
    Color cor;
    bool interage;
    Acoes acao;
};

struct TelaFogao {
    Rectangle painel;            
    float xDivisoria;              
    std::vector<Rectangle> bocas;   
    std::vector<Rectangle> slots;   
    int bocaHover;                  
    int slotHover;                 
};

enum DirecaoAnim {
    DIR_BAIXO = 0,
    DIR_ESQUERDA = 1,
    DIR_DIREITA = 2,
    DIR_CIMA = 3
};

struct AnimJogador {
    Texture2D sheet;      
    int frame;          
    float tempo;          
    DirecaoAnim direcao; 
};

enum ESTADO_PROGRAMA {
    JOGANDO,
    MENU,
    PAUSADO,
    CONFIGS,
    HISTORICO,
    COMO_JOGAR,
    DIFICULDADE
};
