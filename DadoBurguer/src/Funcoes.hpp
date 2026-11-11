#pragma once

#include "raylib.h"
#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"
#include <vector>
#include <string>
#include "Montagem.hpp"

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
TelaEstoque CriarTelaEstoque(float largura, float altura, IngredienteJogo Ingredientes_Para_Passar[19]);
void DescarregarTelaEstoque(TelaEstoque& t);
bool AtualizarTelaEstoque(TelaEstoque& tela, char& escolhidoEST, int& escolhidoINV);
void DesenharIngrediente(const TelaEstoque& tela, char codigo, Rectangle area);
void DesenharTelaEstoque(const TelaEstoque& tela, ListaContiguaINV &inventario);

//MAPA

Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao, int staminaGasta);
void ConstruirMapa(std::vector<Rectangle>& paredes, std::vector<Bloco>& blocos);
void DesenharBloco(const Bloco& b);
std::vector<Rectangle> GerarGrade(Rectangle zona, int colunas, int linhas, float espaco);
TelaFogao CriarTelaFogao(float largura, float altura);
bool AtualizarTelaFogao(TelaFogao& tela, int &escolhidoFogInv, int &escolhidoFogBoc, ListaContiguaINV &inventario);
void DesenharTelaFogao(const TelaFogao& tela, ListaContiguaINV &inv);
void DesenharPlaceholder(Rectangle r, Color cor);
void DrawBlock(const Bloco& b);
void DesenharMundo(const Texture2D& fundo, const std::vector<Bloco>& blocos, const Jogador& jogador, const AnimJogador& anim, const Bloco* alvo, const EstadoJogo& estado, const int &turno, const int &stamina);
void desenhaPanelas(ListaContiguaINV &fogao, const std :: vector<Rectangle> &bocas, const Texture2D &texPanela, const Texture2D &texCarneCrua, const Texture2D &texCarneAssada, const Texture2D &texCarneQueimada, const Texture2D &texFogo, const Texture2D &texOvoFrito, const Texture2D &texOvoCru, const Texture2D &texBaconFrito, const Texture2D &texBaconCru ,int turnoEstraga[4], const Texture2D &texCheddarCru, const Texture2D &texCheddarFeito,const Texture2D &texSuicoCru, const Texture2D &texSuicoFeito, int &turno);
static void desenhaCarne(char c, Vector2 centro, const Texture2D &texCarneCrua, const Texture2D &texCarneAssada, const Texture2D &texCarneQueimada, const Texture2D &texOvoFrito, const Texture2D &texBaconFrito,  const Texture2D &texOvoCru, const Texture2D &texBaconCru, const Texture2D &texCheddarCru, const Texture2D &texCheddarFeito,const Texture2D &texSuicoCru, const Texture2D &texSuicoFeito, float escala);

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

int avlAltura(const NodoAvl *n);
int avlFb(const NodoAvl *n);
const NodoAvl* avlBuscar(NodoAvl *raiz, int dado);
void avlEmOrdem(const NodoAvl *raiz);
void avlInserir(NodoAvl *&raiz, int dado, const std :: string &receita);
void avlRemover(NodoAvl *&raiz, int dado);
void avlDestruir(NodoAvl *&raiz);

//HEAP

static void trocar(IngredienteJogo *a[], int i, int j);
void heapify(IngredienteJogo *a[], int n, int i);
void siftUp(IngredienteJogo *a[], int i);
void buildHeap(IngredienteJogo *a[], int n);

void fpInicializar(FilaPrioridade &fp);
int fpEstaVazia(const FilaPrioridade &fp);
int fpInserir(FilaPrioridade &fp, IngredienteJogo *pIngrediente);
IngredienteJogo* fpMinimo(const FilaPrioridade &fp);
void fpRemoverMinimo(FilaPrioridade &fp);

//LISTA CONTIGUA

void inicializar(ListaContiguaINV &l);
int tamanho(const ListaContiguaINV &l);
int inserir(ListaContiguaINV &l, IngredienteJogo novo, int pos);
IngredienteJogo acessar(const ListaContiguaINV &l, int pos);
int buscar(const ListaContiguaINV &l, int cod);
int remover(ListaContiguaINV &l, int pos);
void destruir(ListaContiguaINV &l);
int buscarIngrediente(const ListaContiguaINV& l, IngredienteJogo *Ingrediente);

// HASH

int hashDivisao(int k, int m);
int hashMultiplicativo(int k, int m);
int hashString(const char *s, int m);

void encInicializar(TabelaEnc &t, int m);
void encInserir(TabelaEnc &t, int chave, const NodoAvl *valor);
const NodoAvl* encBuscar(const TabelaEnc &t, int chave);
int encRemover(TabelaEnc &t, int chave);
void encDestruir(TabelaEnc &t);

//INVENTARIO

TelaInventario CriarTelaInventario(float largura, float altura);
bool AtualizarTelaInventario(TelaInventario& tela, int& clicado);
void DesenharIconeNoSlot(Texture2D tex, Rectangle area);
void DesenharTelaInventario(const TelaInventario& tela, ListaContiguaINV &inventario);
void adicionaNoInventario(char escolhidoEST, ListaContiguaINV &inventario, IngredienteJogo PaoCima, IngredienteJogo PaoBaixo, IngredienteJogo Carne, IngredienteJogo QueijoSuico, IngredienteJogo Ovo, IngredienteJogo Bacon, IngredienteJogo Mostarda, IngredienteJogo Ketchup, IngredienteJogo Alface, IngredienteJogo Tomate, IngredienteJogo Cebola, IngredienteJogo Cheddar, IngredienteJogo Picles );
void removeDoInventario(int escolhidoINV, ListaContiguaINV &inventario);
void DesenharDicaMouse(const char* texto, ListaContiguaINV &inventario, int escolhido);

// MESA DE CORTE

void iniciaTelaMesaCorte(TelaMesaCorte &t, const Texture2D &texFaca);
void desenhaTelaMesaCorte(TelaMesaCorte &t, ListaContiguaINV &inventario, const Texture2D &texFaca, const Texture2D &texCebolaFeita, const Texture2D &texTomateFeito, int &stamina, FilaPrioridade &HEAP);
bool AtualizarTelaCorte(TelaMesaCorte& tela);
void pegaFaca(TelaMesaCorte &t);

// MESA DE MONTAGEM

void iniciaTelaMontagem(TelaMontagem &t);
void desenhaTelaMontagem(const TelaMontagem &t, ListaContiguaINV &inventario);
bool AtualizarTelaMontagem(TelaMontagem& tela);

// JOGABILIDADE

void passaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS);
void desenhaTurno(const int &turno, const int &stamina);
void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &menu, Texture2D &pausa, Texture2D &fundo, Texture2D &paoCima, Texture2D &paoBaixo,Texture2D &cheddar,Texture2D &suico, Texture2D &carne_crua, Texture2D &alface, Texture2D &tomate, Texture2D &ketchup, Texture2D &mostarda, Texture2D &cebola, Texture2D &ovo, Texture2D &bacon, Texture2D &picles);
void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina, FilaPrioridade &heap, TabelaEnc &hash, TelaFogao &telafogao, TelaMesaCorte &telaCorte);
int gastaStamina(int &stamina, const int quantoGasta);
int testaStamina (const int &stamina, const int quantoGasta);
void BotaoPassaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS);
void colocaNoHeapEstragado(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam, int &turno);
IngredienteJogo* enderecoDe(ListaContiguaINV &lista, int i);
void reconstroiHeapDesatualizado(ListaContiguaINV &inventario, FilaPrioridade &heap);
void colocaNoHeapEstragadoSemTurno(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam);
void verificaSeEstragou(FilaPrioridade &comidasEstragam, ListaContiguaINV &inventario, const int &turnoAtual);
void DesenharDicaMouseInventario(const char* texto, ListaContiguaINV &inventario, int escolhido);

// PEDIDOS

bool carregaPedidos(const std::string &nomeArquivo, NodoAvl *&raiz, int &codigoMax, int &codigoMin);
std :: string SorteiaPedidos(NodoAvl *&raiz, int &codigoMax, int &codigoMin, TabelaEnc &hash, int &HIT, int &MISS);

// MERGESORT

static bool vemAntes(const Historico &a, const Historico &b);
static void merge(std::vector<Historico> &v, std::vector<Historico> &aux, int ini, int meio, int fim);
static void mergeSortRec(std::vector<Historico> &v, std::vector<Historico> &aux, int ini, int fim);
void mergeSort(std::vector<Historico> &v);

// FIM JOGO

bool telaDigitarNome(std::string &nome, int pontuacao);
bool salvaPontuacao(const std::string &nomeArquivo, const Historico &h);
int carregaHistorico(const std::string &nomeArquivo, std::vector<Historico> &v);
void imprimeHistorico(const std::vector<Historico> &v, int quantos = 10);
static bool arquivoTerminaEmQuebra(const std::string &nomeArquivo);

// DEBUGGING

void fpImprimir(const FilaPrioridade &fp);
void imprime(ListaContiguaINV inv);
void encImprimir(const TabelaEnc &t);
