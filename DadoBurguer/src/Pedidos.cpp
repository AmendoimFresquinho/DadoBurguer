#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <random>

bool carregaPedidos(const std::string &nomeArquivo, NodoAvl *&raiz, int &codigoMax, int &codigoMin, Log &relatorio) {

    std::ifstream arq(nomeArquivo);
    if (!arq.is_open()){
        std::cout << "NAO ABRIU";
        return false;
    }

    int codigo;
    std::string pedido;

    relatorio.innit();

    while (arq >> codigo >> pedido) {
        relatorio.AVL.nRotacoes += avlInserir(raiz, codigo, pedido);
        relatorio.AVL.nInseridos++;
        if (codigo > codigoMax) codigoMax = codigo;
        if (codigo < codigoMin) codigoMin = codigo;     
    }

    relatorio.AVL.alturaTotal = avlAltura(raiz);
    relatorio.AVL.tempoDeCarregamento = relatorio.stop();

    std :: cout << "\n"<< codigoMax << "\n" << "MAXIMO";
    std :: cout << "\n"<< codigoMin << "\n" << "MINIMO";

    relatorio.AVL.escreverLog(relatorio.file);
    return true;  
}

std :: string SorteiaPedidos(NodoAvl *&raiz, int &codigoMax, int &codigoMin, TabelaEnc &hash, int &HIT, int &MISS, Log& relatorio){

    const NodoAvl* nodo = nullptr;
    do {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(codigoMin, codigoMax); // Pega um random entre os codigos maximo e minimo

    int sorteado = distrib(gen);

    int coli = 0;
    const NodoAvl* NoHash = encBuscar(hash, sorteado, coli);
    relatorio.HASH.colisoes += coli;

    if(NoHash != nullptr){
        HIT++; relatorio.HASH.hits++;
        std :: string RECEITA = NoHash->receita;
        RECEITA.insert(0, 1, 'x');
        return RECEITA;
        //return NoHash->receita;
    } 
           
    int comparacoes = 0;
    relatorio.innit();
    nodo = avlBuscar(raiz, sorteado, comparacoes);
    relatorio.AVL.tempoTotalAcumulado += relatorio.stop();
    relatorio.AVL.nComparacoes += comparacoes;
    if(nodo != nullptr){
            ++relatorio.AVL.nBuscas;
        std::cout << "\nFOI NA ARVORE\n";
        encInserir(hash, sorteado, nodo);
        relatorio.HASH.ocupadas++;
        MISS++; relatorio.HASH.misses++;
        std :: string RECEITA = nodo->receita;
        RECEITA.insert(0, 1, 'x');
        return RECEITA;  
    }

    printf("CLIENTENOVO!");
    } while(nodo == nullptr);

    std :: string RECEITA = nodo->receita;
    RECEITA.insert(0, 1, 'x');

    return RECEITA; 
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