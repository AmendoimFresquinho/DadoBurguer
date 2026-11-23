#pragma once

#include "raylib.h"
#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"
#include <vector>
#include "Vec.hpp"
#include <string>
#include "Montagem.hpp"
#include "Logger.hpp"
#include "Som.hpp"

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
void DesenharMundo(const Texture2D& fundo, const std::vector<Bloco>& blocos, const Jogador& jogador, const AnimJogador& anim, const Bloco* alvo, const EstadoJogo& estado, const int &turno, const int &stamina, const int &processos, const int &pontuacao);
void desenhaPanelas(ListaContiguaINV &fogao, const std :: vector<Rectangle> &bocas, const Texture2D &texPanela, const Texture2D &texCarneCrua, const Texture2D &texCarneAssada, const Texture2D &texCarneQueimada, const Texture2D &texFogo, const Texture2D &texOvoFrito, const Texture2D &texOvoCru, const Texture2D &texBaconFrito, const Texture2D &texBaconCru ,int turnoEstraga[4], const Texture2D &texCheddarCru, const Texture2D &texCheddarFeito,const Texture2D &texSuicoCru, const Texture2D &texSuicoFeito, int &turno);
static void desenhaCarne(char c, Vector2 centro, const Texture2D &texCarneCrua, const Texture2D &texCarneAssada, const Texture2D &texCarneQueimada, const Texture2D &texOvoFrito, const Texture2D &texBaconFrito,  const Texture2D &texOvoCru, const Texture2D &texBaconCru, const Texture2D &texCheddarCru, const Texture2D &texCheddarFeito,const Texture2D &texSuicoCru, const Texture2D &texSuicoFeito, float escala);

//FILAS

void inicializaFila(FilaEnc &f);
int estaVaziaFila(FilaEnc &f);
int enfileira(FilaEnc &f, Cliente &cliente);
int desenfileira(FilaEnc &f, Cliente &ClienteAtendido);
int tamanhoFila(FilaEnc &f);
void liberaFila(FilaEnc &f);

//AVL

int avlAltura(const NodoAvl *n);
int avlFb(const NodoAvl *n);
const NodoAvl* avlBuscar(NodoAvl *raiz, int dado, int& comparacoes);
void avlEmOrdem(const NodoAvl *raiz);
int avlInserir(NodoAvl *&raiz, int dado, const std :: string &receita);
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
int hashString(const char *s, int m);

void encInicializar(TabelaEnc &t, int m);
void encInserir(TabelaEnc &t, int chave, const NodoAvl *valor);
const NodoAvl* encBuscar(const TabelaEnc &t, int chave, int& coli);
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
void desenhaTelaMesaCorte(TelaMesaCorte &t, ListaContiguaINV &inventario, const Texture2D &texFaca, const Texture2D &texCebolaFeita, const Texture2D &texTomateFeito, int &stamina, FilaPrioridade &HEAP, SFX_PACK& sfx);
bool AtualizarTelaCorte(TelaMesaCorte& tela);
void pegaFaca(TelaMesaCorte &t);

// MESA DE MONTAGEM

void iniciaTelaMontagem(TelaMontagem &t);
void desenhaTelaMontagem(TelaMontagem &t, ListaContiguaINV &inventario, Image &tmp_img, FilaPrioridade &HEAP, const int &Turno, TelaInventario &tInv, IngredienteJogo IngredientesV[15]);
bool AtualizarTelaMontagem(TelaMontagem& tela);
Vector2 baseHamburguer(const Rectangle &painel);
void imprimirPilha(const Montagem::Pilha& pilha);

// JOGABILIDADE

void passaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS, Dificuldade &dificuldade, FilaEnc &f);
void desenhaTurno(const int &turno, const int &stamina);
void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &hambuergao, Texture2D &RENDER, Image &IMAGEMHAMBURGUER, Texture2D texturas[]);
void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina, FilaPrioridade &heap, TabelaEnc &hash, TelaFogao &telafogao, TelaMesaCorte &telaCorte, TelaInventario &telaInv, TelaMontagem &telaMonta, Dificuldade &dificuldade, FilaEnc &fila, int &processos, int &pontuacao);
int gastaStamina(int &stamina, const int quantoGasta);
int testaStamina (const int &stamina, const int quantoGasta);
void BotaoPassaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS, Dificuldade &dificuldade, FilaEnc &f);
void colocaNoHeapEstragado(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam, int &turno);
IngredienteJogo* enderecoDe(ListaContiguaINV &lista, int i);
void reconstroiHeapDesatualizado(ListaContiguaINV &inventario, FilaPrioridade &heap);
void colocaNoHeapEstragadoSemTurno(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam);
void verificaSeEstragou(FilaPrioridade &comidasEstragam, ListaContiguaINV &inventario, const int &turnoAtual);
void DesenharDicaMouseInventario(const char* texto, ListaContiguaINV &inventario, int escolhido);
int configuraDificuldadeStamina(Dificuldade &Dificuldade, int &Stamina);
void telaDificuldade(Dificuldade &Dificuldade, Texture2D &tela, Texture2D &facil, Texture2D &medio, Texture2D &dificil, Texture2D &impossivel, int &processos);
void desenhaProcessos(const int &processos);
void pontos(const int &pontuacao);

// PEDIDOS

bool carregaPedidos(const std::string &nomeArquivo, NodoAvl *&raiz, int &codigoMax, int &codigoMin, Log &relatorio);
std :: string SorteiaPedidos(NodoAvl *&raiz, int &codigoMax, int &codigoMin, TabelaEnc &hash, int &HIT, int &MISS, Log& relatorio);
void desenhaPedido(FilaEnc &f, IngredienteJogo Ings[QUANTIDADE_INGREDIENTES], Texture2D &caixaPensamento);

// HISTORICO

static bool vemAntes(const Historico &a, const Historico &b);
static void merge(Vec<Historico> &v, Vec<Historico> &aux, int ini, int meio, int fim);
static void mergeSortRec(Vec<Historico> &v, Vec<Historico> &aux, int ini, int fim);
void mergeSort(Vec<Historico> &v);
void countingSort(Vec<Historico>& v, int posicao, Historico* auxiliar);
void radixSort(Vec<Historico>& v);
int chaveNome(const std::string& nome, int posicao);
void desenhaHistorico(const Vec<Historico>& historico);

// FIM JOGO

bool telaDigitarNome(std::string &nome, int pontuacao);
bool salvaPontuacao(const std::string &nomeArquivo, const Historico &h);
int carregaHistorico(const std::string &nomeArquivo, Vec<Historico> &v);
void imprimeHistorico(const Vec<Historico> &v, int quantos = 10);
static bool arquivoTerminaEmQuebra(const std::string &nomeArquivo);

// CLIENTES

Cliente criaClientePadrao(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, int &codigoMax, int &codigoMin, Log& relatorio);
Cliente CriaclienteEspecial(Texture2D sprites[2]);
void criaFilaClientes(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, Texture2D Especiais[2], FilaEnc &Clientes, int &TAM_FILA, int &codigoMax, int &codigoMin, Log& relatorio);
void desenhaFila(FilaEnc &f);
void checaSeAcertou(FilaEnc &f, int &pontuacao, Dificuldade &dificuldade, int &processos, TelaInventario &telaInv, SFX_PACK& sfx);
void TelaConfirmacao(Texture2D &mainTela, Texture2D &sim, Texture2D &nao, EstadoJogo &estado, FilaEnc &f, int &pontuacao, Dificuldade &dificuldade, int &processos, TelaInventario &telaInv, SFX_PACK& sfx);
bool checaProcessos(int &processos, Dificuldade &dificuldade);
void desenhaBarraPaciencia(const FilaEnc& f, int pacienciaInicial, Texture2D verde, Texture2D vermelho, Texture2D vazio);

// DEBUGGING

void fpImprimir(const FilaPrioridade &fp);
void imprime(ListaContiguaINV inv);
void encImprimir(const TabelaEnc &t);

// EMERGENCIA

void clonarPilhaComVetor(Montagem::Pilha &destino, Montagem::Pilha &origem, TelaMontagem &t, IngredienteJogo IngredientesV[15]);


