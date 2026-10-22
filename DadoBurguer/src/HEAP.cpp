#include <iostream>
#include "Funcoes.hpp"
#include "Structs.hpp"

static void trocar(IngredienteJogo *a[], int i, int j) {
    IngredienteJogo* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(IngredienteJogo *a[], int n, int i) {
    int menor = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && a[esq]->turnoEstraga < a[menor]->turnoEstraga) menor = esq;
    if (dir < n && a[dir]->turnoEstraga < a[menor]->turnoEstraga) menor = dir;

    if (menor != i) {
        trocar(a, i, menor);
        heapify(a, n, menor);
    }
}

void siftUp(IngredienteJogo *a[], int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (a[i]->turnoEstraga < a[pai]->turnoEstraga) {
            trocar(a, i, pai);
            i = pai;
        } 
        else {
            break;
        }
    }
}

void buildHeap(IngredienteJogo *a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

void fpInicializar(FilaPrioridade &fp) {
    fp.tamanho = 0;
}

int fpEstaVazia(const FilaPrioridade &fp) {
    return fp.tamanho == 0;
}

int fpInserir(FilaPrioridade &fp, IngredienteJogo *pIngrediente) {
    if (fp.tamanho >= HEAP_CAP) return 0;
    fp.dados[fp.tamanho] = pIngrediente;
    siftUp(fp.dados, fp.tamanho);
    fp.tamanho++;
    return 1;
}

IngredienteJogo* fpMinimo(const FilaPrioridade &fp) {
    if (fpEstaVazia(fp)) return nullptr;
    return fp.dados[0];
}

void fpRemoverMinimo(FilaPrioridade &fp) {
    fp.tamanho--;
    fp.dados[0] = fp.dados[fp.tamanho];
    heapify(fp.dados, fp.tamanho, 0);
}   