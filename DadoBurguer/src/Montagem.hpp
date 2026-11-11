#pragma once

#include "Ingredientes.hpp"
#include "raylib.h"

namespace Montagem {

    const float ESCALA_ALTURA {1.0f};
    const int MAX_INGREDIENTES {10};
    const int ALTURA_IMAGEM_FUNDO {256};
    const int LARGURA_IMAGEM_FUNDO {64};

    enum err{
        Sucesso = 0,
        MaxIngredientesJaAtingido, // Caso tente adicionar um ingrediente em um hambúrguer já maximizado
        TexturaInvalidaResolvida    // Caso tente mexer com uma textura que esteja invalida mas foi resolvida
    };

    struct Nodo {
        Nodo* prox;
        Ingredientes ingrediente;

        Nodo(Ingredientes arg) : prox(nullptr), ingrediente(arg) {};        // Inicializa com o tipo
        Nodo() : Nodo(Ingredientes::VAZIO) {};                              // Inicializa com Vazio caso não tenha sido passado outro valor
    };

    struct Pilha {
        Montagem::Nodo* topo;   // Ponteiro para o topo
        int quantDados;         // Quantidade de ingredientes na pilha
        float altura;           // Onde desenhar o próximo
        Texture2D textura;      // Textura da pilha
        Image image;            // Imagem da pilha (Igual a textura, mas serve para otimização)

        Pilha() : topo(nullptr), quantDados(0), altura(0.0f) {};

        void empilha(Ingredientes ing){
            Montagem::Nodo* nodo = new Montagem::Nodo(ing);
            nodo->prox = topo;
            topo = nodo;
            ++quantDados;
        };

        Ingredientes desempilha() { // Salva o ingrediente removido
            if (topo == nullptr) return Ingredientes::VAZIO;

            Montagem::Nodo* aux = topo;
            topo = topo->prox;
            Ingredientes retorno = aux->ingrediente;
            --quantDados;

            delete(aux);

            return retorno;
        };

        bool estaVazia(){
            return topo == nullptr;
        };
    };

    float altura(Ingredientes ing);
    char* pegarStringIng(Ingredientes ing);
    Color pegarTintIng(Ingredientes ing);
    void carregarImagem(Ingredientes ing, Image& img);
    void adicionarTextura(Montagem::Pilha& pilha, Image& img);
    void refazerImagemHamburguer(Montagem::Pilha& pilha, Image& img);
    int adicionarIngrediente(Montagem::Pilha& pilha, Ingredientes ing, Image& img);
    void removerIngrediente(Montagem::Pilha& pilha, Image& img);
}