#include <iostream>
#include <iomanip>
#include "Funcoes.hpp"
#include "Structs.hpp"

//PILHAS

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

//FILAS

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

//LISTA SIMPLESMENTE ENCADEADA

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
    else                // removendo do meio ou do final
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

//AVL

