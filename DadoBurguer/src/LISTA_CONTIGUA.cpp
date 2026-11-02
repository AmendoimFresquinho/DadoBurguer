#include "Funcoes.hpp"
#include "Constantes.hpp"
#include "Structs.hpp"
#include <iostream>

void inicializar(ListaContiguaINV &l) {
    l.tamanho = 0;
}

int tamanho(const ListaContiguaINV &l) {
    return l.tamanho;
}

int inserir(ListaContiguaINV& l, IngredienteJogo novo, int pos) {
    int i;

    if (l.tamanho == CAPACIDADE)
        return 0; 

    if (pos > l.tamanho || pos < 0)
        return 0; 

    for (i = l.tamanho; i > pos; i--)
        l.dados[i] = l.dados[i - 1];

    l.dados[pos] = novo;
    l.tamanho++;

    return 1;
}

IngredienteJogo acessar(const ListaContiguaINV& l, int pos) {
    IngredienteJogo iAux;

    if (pos >= l.tamanho || pos < 0)
        iAux.codigo = -1; 
    else
        iAux = l.dados[pos];

    return iAux;
}

int buscar(const ListaContiguaINV& l, char cod) {
    int i;

    for (i = 0; i < l.tamanho; i++) {
        if (l.dados[i].codigo == cod) {
            return i; // posição onde o produto foi encontrado
        }
    }

    return -1; // não encontrado
}

int buscarIngrediente(const ListaContiguaINV& l, IngredienteJogo *Ingrediente) {
    int i;

    for (i = 0; i < l.tamanho; i++) {
        if (&l.dados[i] == Ingrediente) {
            return i; // posição onde o produto foi encontrado
        }
    }
    return -1;
}

int remover(ListaContiguaINV& l, int pos) {
    int i;

    if (pos >= l.tamanho || pos < 0)
        return 0; // posição inválida

    for (i = pos; i < l.tamanho - 1; i++)
        l.dados[i] = l.dados[i + 1];

    l.tamanho--;

    return 1;
}

void destruir(ListaContiguaINV& l) {
    l.tamanho = 0;
}