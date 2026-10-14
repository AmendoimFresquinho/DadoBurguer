#ifndef IMAGENS
#define IMAGENS

#include "ingredientes.hpp"
#include "raylib.h"

#include <string>

namespace Imagens {

    struct Ingredientes {
        Geral::Ingredientes tipo;
        Texture2D textura;
        int paddingInf;
        int paddingSup;

        Ingredientes(Geral::Ingredientes ti, const char* pathTXT, int i, int s) {
            tipo = ti;
            textura = LoadTexture(pathTXT);
            paddingInf = i;
            paddingSup = s;
        }
        ~Ingredientes() {
            UnloadTexture(textura);
        }
    };
}


#endif