#include "Funcoes.hpp"
#include "Structs.hpp"
#include <algorithm>
#include <iostream>
using namespace std;
 
int avlAltura(const NodoAvl *n) {
    return n ? n->altura : -1;
}
 
/* FB = h(esq) - h(dir). Positivo: pesado a esquerda. */
int avlFb(const NodoAvl *n) {
    return n ? avlAltura(n->esq) - avlAltura(n->dir) : 0;
}
 
void atualizarAltura(NodoAvl *n) {
    if (n)
        n->altura = 1 + max(avlAltura(n->esq), avlAltura(n->dir));
}
 
void rotDir(NodoAvl *&y) {
    NodoAvl *x = y->esq;
    y->esq = x->dir;
    x->dir = y;
    atualizarAltura(y);
    atualizarAltura(x);
    y = x; // x vira a nova raiz da subarvore
}
 
void rotEsq(NodoAvl *&x) {
    NodoAvl *y = x->dir;
    x->dir = y->esq;
    y->esq = x;
    atualizarAltura(x);
    atualizarAltura(y);
    x = y; // y vira a nova raiz da subarvore
}

// Retorna o número de rotações necessárias
int  reequilibrar(NodoAvl *&raiz) {
    atualizarAltura(raiz);
    int fb = avlFb(raiz);
    int n = 0;
    if (fb > 1) {
        if (avlFb(raiz->esq) < 0) { // LR
            rotEsq(raiz->esq);
            ++n;
        }
        rotDir(raiz);               // LL
        ++n;
    } else if (fb < -1) {
        if (avlFb(raiz->dir) > 0) { // RL
            rotDir(raiz->dir);
            ++n;
        }
        rotEsq(raiz);               // RR
        ++n;
    }
    return n;
}
 
const NodoAvl* avlBuscar(NodoAvl *raiz, int codigo, int& comparacoes) {
    ++comparacoes;
    if (!raiz) return nullptr;
    if (codigo < raiz->codigo) return avlBuscar(raiz->esq, codigo, comparacoes);
    if (codigo > raiz->codigo) return avlBuscar(raiz->dir, codigo, comparacoes);
    return raiz;
}
// Retorna o número de rotações necessárias
int avlInserir(NodoAvl *&raiz, int codigo, const std :: string &receita) {
    int rot = 0;
    if (!raiz) {
        raiz = new NodoAvl{codigo, receita, 0, nullptr, nullptr};
        return 0;
    }
    if (codigo < raiz->codigo)
        rot += avlInserir(raiz->esq, codigo, receita);
    else if (codigo > raiz->codigo)
        rot += avlInserir(raiz->dir, codigo, receita);
    else
        return 0; // duplicatas ignoradas
 
    return rot += reequilibrar(raiz);
}
 
NodoAvl *minimo(NodoAvl *n) {
    while (n->esq) n = n->esq;
    return n;
}
 
void avlRemover(NodoAvl *&raiz, int codigo) {
    if (!raiz) return;
 
    if (codigo < raiz->codigo) {
        avlRemover(raiz->esq, codigo);
    } else if (codigo > raiz->codigo) {
        avlRemover(raiz->dir, codigo);
    } else {
        if (!raiz->esq || !raiz->dir) {
            NodoAvl *filho = raiz->esq ? raiz->esq : raiz->dir;
            delete raiz;
            raiz = filho;
            return;
        }
        // Dois filhos: substitui pelo menor da subarvore direita
        NodoAvl *suc = minimo(raiz->dir);
        raiz->codigo = suc->codigo;
        avlRemover(raiz->dir, suc->codigo);
    }
    reequilibrar(raiz);
}
 
void avlDestruir(NodoAvl *&raiz) {
    if (!raiz) return;
    avlDestruir(raiz->esq);
    avlDestruir(raiz->dir);
    delete raiz;
    raiz = nullptr;
}
