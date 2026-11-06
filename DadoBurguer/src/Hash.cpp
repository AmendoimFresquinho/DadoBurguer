#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <string>
#include <iostream>
#include <cmath>

int hashDivisao(int k, int m) {
    return k % m;
}

int hashMultiplicativo(int k, int m) {
    constexpr double A = 0.6180339887; // knuth = A  
    double prod = static_cast<double>(k) * A;
    double frac = prod - std::floor(prod);
    return static_cast<int>(m * frac);
}

int hashString(const char *s, int m) {
    const int B = 31;
    int h = 0;
    for (int i = 0; s[i] != '\0'; i++)
        h = (h * B + static_cast<unsigned char>(s[i])) % m;
    return h;
}

void encInicializar(TabelaEnc &t, int m) {
    t.m = m;
    t.n = 0;
    t.tabela = new NoHash*[m];
    for (int i = 0; i < m; i++)
        t.tabela[i] = nullptr;
}

void encInserir(TabelaEnc &t, int chave, const NodoAvl *valor) {
    int i = hashDivisao(chave, t.m);
    NoHash *novo = new NoHash{chave, valor, t.tabela[i]};
    t.tabela[i] = novo;
    t.n++;
}

const NodoAvl* encBuscar(const TabelaEnc &t, int chave) {
    int i = hashDivisao(chave, t.m);
    NoHash *p = t.tabela[i];
    while (p != nullptr) {
        if (p->chave == chave) return p->valor;
        p = p->prox;
    }
    return nullptr;   // não encontrado
}

int encRemover(TabelaEnc &t, int chave) {
    int i = hashDivisao(chave, t.m);
    NoHash *p = t.tabela[i];
    NoHash *ant = nullptr;
    while (p != nullptr) {
        if (p->chave == chave) {
            if (ant == nullptr)
                t.tabela[i] = p->prox;
            else
                ant->prox = p->prox;
            delete p;
            t.n--;
            return 1;
        }
        ant = p;
        p = p->prox;
    }
    return 0;
}

void encDestruir(TabelaEnc &t) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        NoHash *p = t.tabela[i];
        while (p != nullptr) {
            NoHash *prox = p->prox;
            delete p;
            p = prox;
        }
        t.tabela[i] = nullptr;
    }
    t.n = 0;
}