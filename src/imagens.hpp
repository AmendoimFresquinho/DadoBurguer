#pragma once

#include "ingredientes.hpp"
#include "raylib.h"

#include <stdio.h>

#include <string>
#include <vector>


namespace Imagens {
    struct ImagemIngrediente {
        Geral::Ingredientes tipo;
        Texture2D textura;
        int paddingInf;
        int paddingSup;

        ImagemIngrediente(Geral::Ingredientes ti, const char* pathTXT, int i, int s) {
            tipo = ti;
            textura = LoadTexture(pathTXT);
            paddingInf = i;
            paddingSup = s;
        }
        ImagemIngrediente() : tipo(Geral::Ingredientes::VAZIO), textura({0}), paddingInf(0), paddingSup(0) {};

        int desenhar(int x, int y) {
            DrawTexture(textura, x, y - paddingInf, WHITE);
            return paddingInf + paddingSup;
        }
    };
    typedef std::vector<ImagemIngrediente> TxtPack_Ingredientes;
        
    int carregarTextura(TxtPack_Ingredientes &pacote, char* pathTXT, Geral::Ingredientes tipo, int paddingInferior, int paddingSuperior){
        for (const auto& img : pacote){
            if (img.tipo == tipo) return 1;
        }
        pacote.push_back(ImagemIngrediente{tipo, pathTXT, paddingInferior, paddingSuperior});
        
        return 0;
    };


    void desenharHamburguer(Geral::Hamburguer hamburguer, int x, int y, TxtPack_Ingredientes &pacote){
        int offset = 0;
        for (int i = 0; i < hamburguer.altura; i++){
            for (auto& img : pacote){
                if (img.tipo == hamburguer.pilha[i]) {
                    img.desenhar(x, y - offset - img.paddingInf);
                    offset += img.paddingSup;
                    break;
                }
            }
        }
        printf("\n");
    }

    void descarregarPacote(TxtPack_Ingredientes &pacote){
        for(auto& img : pacote) UnloadTexture(img.textura);

        pacote.clear();
    }

}