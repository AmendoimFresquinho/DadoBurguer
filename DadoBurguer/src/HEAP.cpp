#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"

static void trocar(int a[], int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int a[], int n, int i) {
    int menor = i;
    int esq   = 2 * i + 1;
    int dir   = 2 * i + 2;

    if (esq < n && a[esq] < a[menor]) menor = esq;   
    if (dir < n && a[dir] < a[menor]) menor = dir;   

    if (menor != i) {
        trocar(a, i, menor);
        heapify(a, n, menor);
    }
}

void siftUp(int a[], int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (a[i] < a[pai]) {
            trocar(a, i, pai);
            i = pai;
        } else {
            break;
        }
    }
}

void buildHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

void fpInicializar(FilaPrioridade &fp) {
    fp.tamanho = 0;
}

int fpEstaVazia(const FilaPrioridade &fp) {
    return fp.tamanho == 0;
}

int fpInserir(FilaPrioridade &fp, int valor) {
    if (fp.tamanho >= HEAP_CAP) return 0;
    fp.dados[fp.tamanho] = valor;
    siftUp(fp.dados, fp.tamanho);
    fp.tamanho++;
    return 1;
}

int fpMinimo(const FilaPrioridade &fp, int &valor) {
    if (fpEstaVazia(fp)) return 0;
    valor = fp.dados[0];
    return 1;
}

int fpRemoverMinimo(FilaPrioridade &fp, int &valor) {
    if (fpEstaVazia(fp)) return 0;
    valor = fp.dados[0];
    fp.tamanho--;
    fp.dados[0] = fp.dados[fp.tamanho];
    heapify(fp.dados, fp.tamanho, 0);
    return 1;
}