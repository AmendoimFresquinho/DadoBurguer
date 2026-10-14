#pragma once
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raylib.h"
#include <string>

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

typedef struct {
    Nodo *ini;
} ListaEnc;

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

struct EstadoJogo {
    bool fogaoLigado;
    const char* mensagem;     // feedback temporário na tela
    float tempoMensagem;      // segundos restantes
};

struct Jogador {
    float velocidade;
    float tamanho;
    Vector2 posicao;
    Vector2 aceleracao;
};

struct Bloco {
    Rectangle rect;
    std::string nome;
    Texture2D textura;              
    Color cor;
    bool interage;
    Acoes acao;
};

