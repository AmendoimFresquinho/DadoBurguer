#include "Funcoes.hpp"
#include <iostream>
#include "Structs.hpp"

void inicializaPilha(PilhaEnc &p) {
    p.topo = nullptr;
}

int estaVaziaPilha(PilhaEnc &p) {
    return p.topo == nullptr;
}

int empilha(PilhaEnc &p, Produto valor) {
    Nodo *novo = new Nodo;
   
    novo->dado = valor;
    novo->prox = p.topo; 
    p.topo = novo;        
    return 1;
}

int desempilha(PilhaEnc &p, Produto &valorRemovido) {
    Nodo *removido;

    if (estaVaziaPilha(p)) // underflow
        return 0;

    removido = p.topo;
    valorRemovido = removido->dado;
    p.topo = removido->prox;
    delete removido;
    return 1;
}

int topoPilha(PilhaEnc &p, Produto &valor) {
    if (estaVaziaPilha(p))
        return 0;

    valor = p.topo->dado;
    return 1;
}

int tamanhoPilha(PilhaEnc &p) {
    Nodo *aux = p.topo;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void liberaPilha(PilhaEnc &p) {
    Produto lixo;
    while (desempilha(p, lixo)) {}
}