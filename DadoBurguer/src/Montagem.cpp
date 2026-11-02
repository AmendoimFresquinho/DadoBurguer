#include "Funcoes.hpp"
#include <iostream>
#include "Structs.hpp"
#include "Montagem.hpp"
#include "raylib.h"

namespace Montagem{

    float altura(Ingredientes ing){ // Retorna a altura da imagem do ingrediente ing
        switch (ing){
            case Ingredientes::ALFACE: return 1.2f; break;
            case Ingredientes::BACON: return 1.2f; break;
            case Ingredientes::CARNE: return 1.2f; break;
            case Ingredientes::CARNE_ASSADA: return 1.2f; break;
            case Ingredientes::CEBOLA: return 1.2f; break;
            case Ingredientes::CHEDDAR: return 1.2f; break;
            case Ingredientes::KETCHUP: return 0.1f; break;
            case Ingredientes::MOSTARDA: return 0.1f; break;
            case Ingredientes::OVO: return 2.0f; break;
            case Ingredientes::PICLES: return 0.5f; break;
            case Ingredientes::SUICO: return 0.3f; break;
            case Ingredientes::TOMATE: return 0.7f; break;

            case Ingredientes::VAZIO:
            case Ingredientes::PAO_BAIXO:
            case Ingredientes::PAO_CIMA:
            default: return 0.0f;
        }
    };

    char* pegarStringIng(Ingredientes ing){ // Retorna a string (char*) equivalente ao endereço do .png da imagem de ing
        switch (ing){
            case Ingredientes::ALFACE: return (char*)"DadoBurguer/assets/Montagem/Alface.png"; break;              // FEITO
            case Ingredientes::BACON: return (char*)"DadoBurguer/assets/Montagem/Bacon.png"; break;                //
            case Ingredientes::CARNE: return (char*)"DadoBurguer/assets/Montagem/BifeCinza.png"; break;            // FEITO
            case Ingredientes::CARNE_ASSADA: return (char*)"DadoBurguer/assets/Montagem/BifeCinza.png"; break;     // FEITO
            case Ingredientes::CEBOLA: return (char*)"DadoBurguer/assets/Montagem/Cebola.png"; break;              //
            case Ingredientes::CHEDDAR: return (char*)"DadoBurguer/assets/Montagem/Cheddar.png"; break;            // FEITO
            case Ingredientes::KETCHUP: return (char*)"DadoBurguer/assets/Montagem/Ketchup.png"; break;            //
            case Ingredientes::MOSTARDA: return (char*)"DadoBurguer/assets/Montagem/Mostarda.png"; break;          //
            case Ingredientes::OVO: return (char*)"DadoBurguer/assets/Montagem/Ovo.png"; break;                    //
            case Ingredientes::PICLES: return (char*)"DadoBurguer/assets/Montagem/Picles.png"; break;              //
            case Ingredientes::SUICO: return (char*)"DadoBurguer/assets/Montagem/Suico.png"; break;                //
            case Ingredientes::TOMATE: return (char*)"DadoBurguer/assets/Montagem/Tomate.png"; break;              // FEITO
            case Ingredientes::PAO_BAIXO: return (char*)"DadoBurguer/assets/Montagem/Pao_Baixo.png"; break;        // FEITO
            case Ingredientes::PAO_CIMA: return (char*)"DadoBurguer/assets/Montagem/Pao_Cima.png"; break;          //

            case Ingredientes::VAZIO:                                                           //
            default: return (char*)"assets/Montagem/Vazio.png";
        }
    };
    Color pegarTintIng(Ingredientes ing){ // Retorna a tonalidade para tal ingrediente
        switch (ing) {
            case Ingredientes::CARNE:           return (Color) {181, 14, 14, 255}; break;
            case Ingredientes::CARNE_ASSADA:    return (Color) {99, 46, 28, 255}; break;

            default: return WHITE; break;
        };
    };
    /*
    @param ing Ingrediente para carregar
    @param &img Imagem de destino
    @brief Carrega a imagem para img e já aplica a tonalidade correta
    */
    void carregarImagem(Ingredientes ing, Image& img){
        img = LoadImage(pegarStringIng(ing));
        ImageColorTint(&img, pegarTintIng(ing));
    };

    void adicionarTextura(Montagem::Pilha& pilha, Image& img){
        Image imgPilha = LoadImageFromTexture(pilha.textura);
        ImageDrawImage(&imgPilha, img, 0, pilha.altura, WHITE);
        UnloadTexture(pilha.textura);
        pilha.textura = LoadTextureFromImage(imgPilha);
        UnloadImage(imgPilha);
    };

    void refazerImagemHamburguer(Montagem::Pilha& pilha, Image& img1, Image& img2){
        UnloadTexture(pilha.textura);
        UnloadImage(img1);
        UnloadImage(img2);

        img1 = LoadImage(pegarStringIng(Ingredientes::PAO_BAIXO)); // Carrega o pão de baixo
        Ingredientes ing;
        Montagem::Pilha reversa {};

        while (!pilha.estaVazia()){             // Faz o xamburgui reverso
            reversa.empilha(pilha.desempilha());
        };

        while (!reversa.estaVazia()){             // Faz o xamburgui normal
            ing = reversa.desempilha();
            carregarImagem(ing, img2);
            ImageDrawImage(&img1, img2, 0, pilha.altura, WHITE);
            pilha.empilha(ing);
            pilha.altura += altura(ing);

        }

        UnloadImage(img2);
        pilha.textura = LoadTextureFromImage(img1);
        UnloadImage(img1);
    };

    /*
    @param pilha Pilha do hambúrguer
    @param ing Ingrediente a adicionar
    @param &img Imagem qualquer, será substituída. Serve para que ela seja inicalizada no main.cpp e faça funcionar com a raylib
    @return Tipo de erro (Montagem::err)
    */
    int adicionarIngrediente(Montagem::Pilha& pilha, Ingredientes ing, Image& img){
        if (pilha.quantDados >= MAX_INGREDIENTES) return Montagem::err::MaxIngredientesJaAtingido;
        if (!IsTextureValid(pilha.textura)) {
            pilha.textura = LoadTexture("DadoBurguer/assets/Montagem/Pao_Baixo.png");
            return Montagem::err::TexturaInvalidaResolvida;
        }
        pilha.empilha(ing);

        carregarImagem(ing, img);

        adicionarTextura(pilha, img);

        pilha.altura += altura(ing);

        return Montagem::err::Sucesso;
    };

    void removerIngrediente(Montagem::Pilha& pilha, Image& img1, Image& img2){
        pilha.desempilha();

        refazerImagemHamburguer(pilha, img1, img2);
    };
}