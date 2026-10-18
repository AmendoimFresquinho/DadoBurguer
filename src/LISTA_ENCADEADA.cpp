#include "Funcoes.hpp"
#include <iostream>
#include <iomanip>
#include "Structs.hpp"

void inicializar(ListaEnc &lista) {
    lista.ini = nullptr;
}

int tamanho(const ListaEnc &lista) {
    Nodo *aux = lista.ini;
    int contador = 0;

    while (aux != nullptr) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void imprimir(const ListaEnc &lista) {
    Nodo *aux = lista.ini;

    while (aux != nullptr) {
        std::cout << "Codigo: " << aux->dado.cod << "\n";
        std::cout << "Nome: " << aux->dado.nome << "\n";
        std::cout << "Preco: " << std::fixed << std::setprecision(2) << aux->dado.preco << "\n";
        aux = aux->prox;
    }
}

Produto buscar(const ListaEnc &lista, int cod) {
    Produto prod = {0, "", 0.0f};
    Nodo *aux = lista.ini;

    while (aux != nullptr) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod; // não encontrado: produto "vazio"
}

int inserirInicio(ListaEnc &lista, const Produto &prod) {
    Nodo *novo = new Nodo;

    novo->dado = prod;
    novo->prox = lista.ini; // o novo nodo aponta para o antigo início
    lista.ini = novo;       // o novo nodo passa a ser o início

    return 1;
}

int inserirFim(ListaEnc &lista, const Produto &prod) {
    Nodo *novo = new Nodo;

    novo->dado = prod;
    novo->prox = nullptr;

    if (lista.ini == nullptr) { // lista vazia: o novo nodo é o único (e o início)
        lista.ini = novo;
    } else {
        Nodo *aux = lista.ini;
        while (aux->prox != nullptr) // percorre até o último nodo
            aux = aux->prox;
        aux->prox = novo;
    }

    return 1;
}

int removerPorCod(ListaEnc &lista, int cod) {
    Nodo *ant = nullptr;
    Nodo *aux = lista.ini;

    while (aux != nullptr && aux->dado.cod != cod) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == nullptr) // não encontrado
        return 0;

    if (ant == nullptr) // removendo o primeiro nodo
        lista.ini = aux->prox;
    else // removendo do meio ou do final
        ant->prox = aux->prox;

    delete aux;
    return 1;
}

void destruir(ListaEnc &lista) {
    Nodo *aux = lista.ini;

    while (aux != nullptr) {
        Nodo *ant = aux;
        aux = aux->prox;
        delete ant;
    }

    lista.ini = nullptr;
}