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

int enfileira(FilaEnc &f, Cliente &cliente) {
    NodoFila* novo = new NodoFila;

    novo->dado = cliente;
    novo->prox = nullptr;

    if (f.fim != nullptr)
        f.fim->prox = novo;
    else
        f.frente = novo; // Primeiro nó da fila.

    f.fim = novo;
    return 1;
}

int desenfileira(FilaEnc &f, Cliente &ClienteAtendido) {
    NodoFila *removido;

    if (estaVaziaFila(f)) 
        return 0;

    removido = f.frente;
    ClienteAtendido = removido->dado;
    f.frente = removido->prox;

    if (f.frente == nullptr) // a fila ficou vazia
        f.fim = nullptr;

    delete removido;
    return 1;
}

int tamanhoFila(FilaEnc &f) {
    NodoFila *aux = f.frente;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void liberaFila(FilaEnc &f) {
    Cliente lixo;
    while (desenfileira(f, lixo)) {}
}