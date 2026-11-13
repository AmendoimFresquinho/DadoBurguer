#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <random>

bool carregaPedidos(const std::string &nomeArquivo, NodoAvl *&raiz, int &codigoMax, int &codigoMin) {

    std::ifstream arq(nomeArquivo);
    if (!arq.is_open()){
        std::cout << "NAO ABRIU";
        return false;
    }

    int codigo;
    std::string pedido;

    while (arq >> codigo >> pedido) {
        avlInserir(raiz, codigo, pedido);
        if (codigo > codigoMax) codigoMax = codigo;
        if (codigo < codigoMin) codigoMin = codigo;     
    }

    std :: cout << "\n"<< codigoMax << "\n" << "MAXIMO";
    std :: cout << "\n"<< codigoMin << "\n" << "MINIMO";

    return true;  
}

std :: string SorteiaPedidos(NodoAvl *&raiz, int &codigoMax, int &codigoMin, TabelaEnc &hash, int &HIT, int &MISS){

    const NodoAvl* nodo = nullptr;

    do {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(codigoMin, codigoMax); // Pega um random entre os codigos maximo e minimo

    int sorteado = distrib(gen);

    const NodoAvl* NoHash = encBuscar(hash, sorteado);

    if(NoHash != nullptr){
        HIT++;
        return NoHash->receita;
    } 
             
    nodo = avlBuscar(raiz, sorteado);
    
    if(nodo != nullptr){
        std::cout <<"\nFOI NA ARVORE\n";
        encInserir(hash, sorteado, nodo);
        MISS++;
        return nodo->receita;  
    }

    } while(nodo == nullptr);

    return nodo->receita; 
}

void encImprimir(const TabelaEnc &t) { // TEMP
    std::cout << "Hash (n = " << t.n << ")\n";

    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (t.tabela[i] == nullptr)
            continue;                       // pula os baldes vazios

        std::cout << "[" << i << "]";
        for (NoHash *p = t.tabela[i]; p != nullptr; p = p->prox)
            std::cout << " -> " << p->chave;
        std::cout << "\n";
    }
}