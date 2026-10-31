#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <random>


bool carregaPedidos(const std::string &nomeArquivo, NodoAvl *&raiz, int &tamanhoAVL) {

    std::ifstream arq(nomeArquivo);
    if (!arq.is_open()){
        std::cout << "NAO ABRIU";
        return false;
    }

    int codigo;
    std::string pedido;

    while (arq >> codigo >> pedido) {
        avlInserir(raiz, codigo, pedido);
        tamanhoAVL++; // limite para o random depois
    }

    return true;  
}

std :: string SorteiaPedidos(NodoAvl *&raiz, int &tamanhoAVL){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, tamanhoAVL);

    int sorteado = distrib(gen);

    std :: cout << "\n\n\n"<< sorteado << "\n\n\n\n";

    return avlBuscar(raiz, sorteado);
}

