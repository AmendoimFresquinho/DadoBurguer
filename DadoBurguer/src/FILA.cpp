#include "Funcoes.hpp"
#include <iostream>
#include "Structs.hpp"

void inicializaFila(FilaEnc &f) {
    f.frente = nullptr;
    f.fim = nullptr;
}

int estaVaziaFila(FilaEnc &f) {
    return f.frente == nullptr;
}

int enfileira(FilaEnc &f, Produto valor) {
    Nodo *novo = new Nodo;
   
    novo->dado = valor;
    novo->prox = nullptr;

    if (f.fim != nullptr)
        f.fim->prox = novo; // o antigo final passa a apontar para o novo nodo
    else
        f.fim = novo;      // fila estava vazia: novo nodo também é a frente

    f.fim = novo;
    return 1;
}

int desenfileira(FilaEnc &f, Produto &valorRemovido) {
    Nodo *removido;

    if (estaVaziaFila(f)) // underflow
        return 0;

    removido = f.frente;
    valorRemovido = removido->dado;
    f.frente = removido->prox;

    if (f.frente == nullptr) // a fila ficou vazia
        f.fim = nullptr;

    delete removido;
    return 1;
}

int tamanhoFila(FilaEnc &f) {
    Nodo *aux = f.frente;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void liberaFila(FilaEnc &f) {
    Produto lixo;
    while (desenfileira(f, lixo)) {}
}