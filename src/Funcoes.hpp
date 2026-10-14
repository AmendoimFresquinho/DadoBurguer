#pragma once
#include "Funcoes.hpp"
#include "Structs.hpp"

//PILHAS

void inicializaPilha(PilhaEnc &p);
int estaVaziaPilha(PilhaEnc &p);
int empilha(PilhaEnc &p, Produto valor);
int desempilha(PilhaEnc &p, Produto &valorRemovido);
int topoPilha(PilhaEnc &p, Produto &valor);
int tamanhoPilha(PilhaEnc &p);
void liberaPilha(PilhaEnc &p);

//FILAS

void inicializaFila(FilaEnc &f);
int estaVaziaFila(FilaEnc &f);
int enfileira(FilaEnc &f, Produto valor);
int desenfileira(FilaEnc &f, Produto &valorRemovido);
int tamanhoFila(FilaEnc &f);
void liberaFila(FilaEnc &f);

//LISTA SIMPLESMENTE ENCADEADA

void inicializar(ListaEnc *lista);
void imprimir(const ListaEnc *lista);
Produto buscar(const ListaEnc *lista, int cod);
int inserirInicio(ListaEnc *lista, Produto prod);
int inserirFim(ListaEnc *lista, Produto prod);
int removerPorCod(ListaEnc *lista, int cod);
void destruir(ListaEnc *lista);
int tamanho(const ListaEnc *lista);

//AVL

NodoAvl *avlBuscar(NodoAvl *raiz, int dado);
NodoAvl *avlInserir(NodoAvl *raiz, int dado);
NodoAvl *avlRemover(NodoAvl *raiz, int dado);
NodoAvl *avlDestruir(NodoAvl *raiz);
