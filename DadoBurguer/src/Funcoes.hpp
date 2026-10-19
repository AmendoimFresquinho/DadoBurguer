#pragma once

#include "raylib.h"
#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>

//PLAYER

void Movimentacao(Jogador& player);
void Colisoes(Jogador& player, float dt, const std::vector<Rectangle>& solids);
Bloco* ProcuraInteragir(const Jogador& player, std::vector<Bloco>& blocks, float reach);
void FazInteracao(const Bloco& block, EstadoJogo& state);
AnimJogador CriarAnimJogador(const char* arquivo);
Rectangle HitBox(const Jogador& p);
void DesenharAnimJogador(const AnimJogador& a, Rectangle hitbox);
void AtualizarAnimJogador(AnimJogador& a, Vector2 deslocamento, float dt);
void DescarregarAnimJogador(AnimJogador& a); 
TelaEstoque CriarTelaEstoque(float largura, float altura,IngredienteJogo PaoCima, IngredienteJogo PaoBaixo, IngredienteJogo Carne, IngredienteJogo QueijoSuico, IngredienteJogo Ovo, IngredienteJogo Bacon, IngredienteJogo Mostarda, IngredienteJogo Ketchup, IngredienteJogo Alface, IngredienteJogo Tomate, IngredienteJogo Cebola, IngredienteJogo Cheddar, IngredienteJogo Picles );
void DescarregarTelaEstoque(TelaEstoque& t);
bool AtualizarTelaEstoque(TelaEstoque& tela, char& escolhidoEST, int& escolhidoINV);
void DesenharIngrediente(const TelaEstoque& tela, char codigo, Rectangle area);
void DesenharTelaEstoque(const TelaEstoque& tela, ListaContiguaINV &inventario);

//MAPA

Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao);
void ConstruirMapa(std::vector<Rectangle>& paredes, std::vector<Bloco>& blocos);
void DesenharBloco(const Bloco& b);
std::vector<Rectangle> GerarGrade(Rectangle zona, int colunas, int linhas, float espaco);
TelaFogao CriarTelaFogao(float largura, float altura);
bool AtualizarTelaFogao(TelaFogao& tela);
void DesenharTelaFogao(const TelaFogao& tela, ListaContiguaINV &inv);
void DesenharPlaceholder(Rectangle r, Color cor);
void DrawBlock(const Bloco& b);
void DesenharMundo(const Texture2D& fundo, const std::vector<Bloco>& blocos, const Jogador& jogador, const AnimJogador& anim, const Bloco* alvo, const EstadoJogo& estado, const int &turno, const int &stamina);

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

//HEAP

void heapify(int a[], int n, int i);
void siftUp(int a[], int i);
void buildHeap(int a[], int n);

void fpInicializar(FilaPrioridade &fp);
int fpEstaVazia(const FilaPrioridade &fp);
int fpInserir(FilaPrioridade &fp, int valor);
int fpMinimo(const FilaPrioridade &fp, int &valor);
int fpRemoverMinimo(FilaPrioridade &fp, int &valor);

//LISTA CONTIGUA

void inicializar(ListaContiguaINV &l);
int tamanho(const ListaContiguaINV &l);
int inserir(ListaContiguaINV &l, IngredienteJogo novo, int pos);
IngredienteJogo acessar(const ListaContiguaINV &l, int pos);
int buscar(const ListaContiguaINV &l, int cod);
int remover(ListaContiguaINV &l, int pos);
void destruir(ListaContiguaINV &l);

//INVENTARIO

TelaInventario CriarTelaInventario(float largura, float altura);
bool AtualizarTelaInventario(TelaInventario& tela, int& clicado);
void DesenharIconeNoSlot(Texture2D tex, Rectangle area);
void DesenharTelaInventario(const TelaInventario& tela, const ListaContiguaINV &inventario);
void adicionaNoInventario(char escolhidoEST, ListaContiguaINV &inventario, IngredienteJogo PaoCima, IngredienteJogo PaoBaixo, IngredienteJogo Carne, IngredienteJogo QueijoSuico, IngredienteJogo Ovo, IngredienteJogo Bacon, IngredienteJogo Mostarda, IngredienteJogo Ketchup, IngredienteJogo Alface, IngredienteJogo Tomate, IngredienteJogo Cebola, IngredienteJogo Cheddar, IngredienteJogo Picles );
void removeDoInventario(int escolhidoINV, ListaContiguaINV &inventario);
void imprime(ListaContiguaINV inv);
void DesenharDicaMouse(const char* texto);

// JOGABILIDADE

void passaTurno(int &turno, int &stamina);
void desenhaTurno(const int &turno, const int &stamina);
void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &menu, Texture2D &pausa, Texture2D &fundo, Texture2D &paoCima, Texture2D &paoBaixo,Texture2D &cheddar,Texture2D &suico, Texture2D &carne_crua, Texture2D &alface, Texture2D &tomate, Texture2D &ketchup, Texture2D &mostarda, Texture2D &cebola, Texture2D &ovo, Texture2D &bacon, Texture2D &picles);
void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina);
