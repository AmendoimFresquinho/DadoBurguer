#pragma once
#include "Funcoes.hpp"
#include "Structs.hpp"

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
