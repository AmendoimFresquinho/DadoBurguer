#include "Funcoes.hpp"
#include <iostream>
#include "Structs.hpp"
#include "Montagem.hpp"
#include "raylib.h"

namespace Montagem{

    float altura(Ingredientes ing){ // Retorna a altura da imagem do ingrediente ing
        switch (ing){
            case Ingredientes::ALFACE: return 2.1f; break;
            case Ingredientes::BACON: return 1.2f; break;
            case Ingredientes::CARNE: return 4.1f; break;
            case Ingredientes::CARNE_ASSADA: return 4.1f; break;
            case Ingredientes::CARNE_QUEIMADA: return 4.1f; break;
            case Ingredientes::CEBOLA: return 1.2f; break;
            case Ingredientes::CHEDDAR: return 1.2f; break;
            case Ingredientes::KETCHUP: return 0.8f; break;
            case Ingredientes::MOSTARDA: return 0.8f; break;
            case Ingredientes::OVO: return 2.0f; break;
            case Ingredientes::PICLES: return 1.3f; break;
            case Ingredientes::SUICO: return 1.5f; break;
            case Ingredientes::TOMATE: return 1.7f; break;
            case Ingredientes::PAO_BAIXO: return 6.0f; break;
            case Ingredientes::PAO_CIMA: return 12.0f; break;

            case Ingredientes::VAZIO:
            default: return 0.0f;
        }
    };

    char* pegarStringIng(Ingredientes ing){ // Retorna a string (char*) equivalente ao endereço do .png da imagem de ing
        switch (ing){
            case Ingredientes::ALFACE: return (char*)"DadoBurguer/assets/Montagem/Alface.png"; break;              // FEITO
            case Ingredientes::BACON: return (char*)"DadoBurguer/assets/Montagem/Bacon.png"; break;                //
            case Ingredientes::CARNE: return (char*)"DadoBurguer/assets/Montagem/BifeCinza.png"; break;            // FEITO
            case Ingredientes::CARNE_ASSADA: return (char*)"DadoBurguer/assets/Montagem/BifeCinza.png"; break;     // FEITO
            case Ingredientes::CARNE_QUEIMADA: return (char*)"DadoBurguer/assets/Montagem/BifeCinza.png"; break;   // FEITO
            case Ingredientes::CEBOLA: return (char*)"DadoBurguer/assets/Montagem/Cebola.png"; break;              //
            case Ingredientes::CHEDDAR: return (char*)"DadoBurguer/assets/Montagem/Cheddar.png"; break;            // FEITO
            case Ingredientes::KETCHUP: return (char*)"DadoBurguer/assets/Montagem/Ketchup.png"; break;            //
            case Ingredientes::MOSTARDA: return (char*)"DadoBurguer/assets/Montagem/Mostarda.png"; break;          //
            case Ingredientes::OVO: return (char*)"DadoBurguer/assets/Montagem/Ovo.png"; break;                    //
            case Ingredientes::PICLES: return (char*)"DadoBurguer/assets/Montagem/Picles.png"; break;              //
            case Ingredientes::SUICO: return (char*)"DadoBurguer/assets/Montagem/Suico.png"; break;                //
            case Ingredientes::TOMATE: return (char*)"DadoBurguer/assets/Montagem/Tomate.png"; break;              // FEITO
            case Ingredientes::PAO_BAIXO: return (char*)"DadoBurguer/assets/Montagem/Pao_BaixoEmp.png"; break;        // FEITO
            case Ingredientes::PAO_CIMA: return (char*)"DadoBurguer/assets/Montagem/Pao_Cima.png"; break;          //

            case Ingredientes::VAZIO:                                                           //
            default: return (char*)"DadoBurguer/assets/Montagem/Vazio.png";
        }
    };
    Color pegarTintIng(Ingredientes ing){ // Retorna a tonalidade para tal ingrediente
        switch (ing) {
            case Ingredientes::CARNE:           return (Color) {181, 14, 14, 255}; break;
            case Ingredientes::CARNE_ASSADA:    return (Color) {99, 46, 28, 255}; break;
            case Ingredientes::CARNE_QUEIMADA:    return (Color) {20, 20, 20, 255}; break;

            default: return WHITE; break;
        };
    };
    /*
    @param ing Ingrediente para carregar
    @param &img Imagem de destino
    @brief Carrega a imagem para img e já aplica a tonalidade correta
    */
    void carregarImagem(Ingredientes ing, Image& img){
        //if (img.data != nullptr && IsImageValid(img)) UnloadImage(img);
        img = LoadImage(pegarStringIng(ing));
        ImageColorTint(&img, pegarTintIng(ing));
    };

    void adicionarTextura(Montagem::Pilha& pilha, Image& img){
        //Image imgPilha = LoadImageFromTexture(pilha.textura);
        //ImageDrawImage(&imgPilha, img, 0, pilha.altura, WHITE);
        ImageDrawImage(&pilha.image, img, 0, pilha.altura+(Montagem::ALTURA_IMAGEM_FUNDO/2), WHITE);
        //if (IsTextureValid(pilha.textura)) UnloadTexture(pilha.textura);
        //pilha.textura = LoadTextureFromImage(imgPilha);
        //UnloadImage(imgPilha);
        UpdateTexture(pilha.textura, pilha.image.data);
    };

    void refazerImagemHamburguer(Montagem::Pilha& pilha, Image& img){
        //if (img.data != nullptr && IsImageValid(img)) UnloadImage(img); <-- Isso era para prevenir bugs, mas por alguma razão faz o programa crashar. Comentei caso alguém entenda o motivo para não funcionar. #Perdi4DiasPorqueSim #Socorro #OdeioMinhaVida
        pilha.altura = 0;
        //Image imgPilha = LoadImage(pegarStringIng(Ingredientes::VAZIO)); // Carrega o vazio
        if (IsImageValid(pilha.image)) UnloadImage(pilha.image);
        pilha.image = GenImageColor(Montagem::LARGURA_IMAGEM_FUNDO, Montagem::ALTURA_IMAGEM_FUNDO, BLANK);
        Ingredientes ing;
        Montagem::Pilha reversa {};


        while (!pilha.estaVazia()){             // Faz o xamburgui reverso
            ing = pilha.desempilha();
            reversa.empilha(ing);
        };

        while (!reversa.estaVazia()){             // Faz o xamburgui normal
            ing = reversa.desempilha();
            carregarImagem(ing, img);
            //ImageDrawImage(&imgPilha, img, 0, pilha.altura, WHITE);
            ImageDrawImage(&pilha.image, img, 0, pilha.altura+(Montagem::ALTURA_IMAGEM_FUNDO/2), WHITE);
            pilha.empilha(ing);
            pilha.altura -= altura(ing);
            UnloadImage(img);
        }

        //pilha.textura = LoadTextureFromImage(imgPilha);
        if (IsTextureValid(pilha.textura)) UpdateTexture(pilha.textura, pilha.image.data);
        else pilha.textura = LoadTextureFromImage(pilha.image);
        //UnloadImage(imgPilha);
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
            if (!IsImageValid(pilha.image)) pilha.image = GenImageColor(Montagem::LARGURA_IMAGEM_FUNDO, Montagem::ALTURA_IMAGEM_FUNDO, BLANK);
            pilha.textura = LoadTextureFromImage(pilha.image);
            return Montagem::err::TexturaInvalidaResolvida;
        }
        pilha.empilha(ing);

        carregarImagem(ing, img);

        adicionarTextura(pilha, img);

        pilha.altura -= altura(ing);

        return Montagem::err::Sucesso;
    };

    void removerIngrediente(Montagem::Pilha& pilha, Image& img){
        pilha.desempilha();

        refazerImagemHamburguer(pilha, img);
    };

    void clonarPilha(Montagem::Pilha &destino, Montagem::Pilha &origem){
        Montagem::Pilha aux {};
        Ingredientes ing;

        while(!origem.estaVazia()){ aux.empilha(origem.desempilha());};

        while(!aux.estaVazia()){
            ing = aux.desempilha();
            origem.empilha(ing);
            destino.empilha(ing);
        }

        destino.image = ImageCopy(origem.image);
        destino.textura = LoadTextureFromImage(destino.image);
        destino.altura = origem.altura;
    }
}