#pragma once
#include "Structs.hpp"
#include "Constantes.hpp"
#include "raylib.h"
#include <string>
#include <vector>
#include "Ingredientes.hpp"
#include "Montagem.hpp"


struct Produto{
    int cod;
    char nome[50];
    float preco;
};

struct Nodo {
    Nodo *prox;
    Produto dado;
};

struct ListaEnc {
    Nodo *ini;
};

struct PilhaEnc {
    Nodo *topo;
};

struct NodoAvl {
    int codigo;
    std :: string receita;
    int altura;
    struct NodoAvl *esq;
    struct NodoAvl *dir;
};

struct NoHash {
    int chave;
    const NodoAvl *valor;
    NoHash *prox;
};

struct TabelaEnc {
    int m = 0;                  // tamanho da tabela
    int n = 0;                  // quantidade de chaves guardadas
    NoHash **tabela = nullptr;  // vetor de m listas
};

enum Acoes {
    SEM_ACAO,
    ABRIR_FOGAO,
    ACAO_ABRIR_ESTOQUE,
    ACAO_CORTAR,
    ACAO_ATENDER,
    ACAO_ABRIR_INVENTARIO,
    ACAO_MONTAR
};

enum Tela {
    TELA_JOGO,
    TELA_FOGAO,
    TELA_ESTOQUE,
    TELA_INVENTARIO,
    TELA_MONTAGEM,
    TELA_CORTE
};

struct EstadoJogo {
    bool fogaoLigado; // Inutil (nao sei se vai dar bo se tirar)
    Tela tela;
};

struct Jogador {
    float velocidade;
    float tamanho;
    Vector2 posicao;
    Vector2 aceleracao;
    float larguraHit;    
    float alturaHit;     
};

struct Bloco {
    Rectangle rect;
    std::string nome;
    Texture2D textura;              
    Color cor;
    bool interage;
    Acoes acao;
    int staminaGasta;
};

struct IngredienteJogo {
    char codigo;
    bool ehPerecivel;
    Texture2D textura;      
    std :: string nome;
    int turnoEstraga;
};

struct ListaContiguaINV{
    int tamanho;
    IngredienteJogo dados[CAPACIDADE];
};

struct TelaFogao {
    Rectangle painel;            
    float xDivisoria;              
    std::vector<Rectangle> bocas;   
    std::vector<Rectangle> slots;   
    int bocaHover;                  
    int slotHover;
    ListaContiguaINV carnes;
};

enum DirecaoAnim {
    DIR_BAIXO,
    DIR_ESQUERDA,
    DIR_DIREITA,
    DIR_CIMA 
};

struct AnimJogador {
    Texture2D sheet;      
    int frame;          
    float tempo;          
    DirecaoAnim direcao; 
};

enum ESTADO_PROGRAMA {
    JOGANDO,
    MENU,
    PAUSADO,
    RANKING,
    HISTORICO,
    COMO_JOGAR,
    DIFICULDADE,
    FIM_JOGO
};

struct Historico {
    std::string nome;
    int pontuacao;
};

struct TelaEstoque {
    Rectangle painel;
    float xDivisoria;
    Rectangle zonaEsq;
    Rectangle zonaDir;
    std::vector<IngredienteJogo> ingredientes;
    std::vector<Rectangle> celulas;          
    std::vector<Rectangle> slotsInventario;  
    int ingredienteHover;                    
    int slotHover;       
}; 

struct FilaPrioridade {
    IngredienteJogo *dados[HEAP_CAP];
    int tamanho = 0;
};

struct TelaInventario {
    Rectangle painel;
    std::vector<Rectangle> slots;   
    int slotHover; 
    int hamHover;
    Rectangle RecHamburguer;
    Montagem :: Pilha hamburguer;  
    bool temHamburgui;             
};

struct TelaMesaCorte {
    Rectangle moldura;
    Rectangle tabua;
    Rectangle painelFaca;
    Rectangle gradeInv;
    std::vector<Rectangle> slotsInv;   // 9 slots, 3x3

    IngredienteJogo itemTabua;   
    bool temNaTabua = false;   

    Rectangle faca;                    
    Vector2 facaRepouso;               
    float escalaFaca = 1.0f;
    bool facaPegada = false;
    Vector2 offsetPegada = {0, 0};  

    int slotHover = -1;
    int tabuaHover = -1;
    int escolhidoINV = -1;
    int escolhidoTabua = -1;
};

struct TelaMontagem {
    // layout (calculado em iniciaTelaMontagem)
    Rectangle moldura;
    Rectangle painelHamb;
    Rectangle painelInv;
    Rectangle slotHam;
    std::vector<Rectangle> slotsInv;   // 9 slots, 3x3

    // conteúdo
    Montagem :: Pilha hamburguer;
    IngredienteJogo IngsNoHamburger[10];           

    // interação
    int hamHover = -1;
    int slotHover = -1;
    int escolhidoINV = -1;
};

enum Dificuldade {
    FACIL,
    MEDIO,
    DIFICIL,
    IMPOSSIVEL
};

struct Cliente {
    int Paciencia;
    Texture2D sprite;
    std :: string pedido;  
    bool ehEspecial;
};

struct NodoFila {
    NodoFila *prox;
    Cliente dado;
};

struct FilaEnc {
    NodoFila* frente = nullptr;
    NodoFila* fim = nullptr;
};