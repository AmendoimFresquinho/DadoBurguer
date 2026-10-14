#pragma once
#include "raylib.h"
#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>

void Movimentacao(Jogador& player);
void Colisoes(Jogador& player, float dt, const std::vector<Rectangle>& solids);
Bloco* ProcuraInteragir(const Jogador& player, std::vector<Bloco>& blocks, float reach);
void FazInteracao(const Bloco& block, EstadoJogo& state);
void DrawBlock(const Bloco& b);
Rectangle HitBox(const Jogador& p);
void MostrarMensagem(EstadoJogo& estado, const char* texto); //TEMPORARIO
Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao);
void ConstruirMapa(std::vector<Rectangle>& paredes, std::vector<Bloco>& blocos);
void DesenharBloco(const Bloco& b);

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
