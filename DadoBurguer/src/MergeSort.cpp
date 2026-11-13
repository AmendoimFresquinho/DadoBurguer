//#include <vector>
#include "Vec.hpp"
#include "Structs.hpp"

static bool vemAntes(const Historico &a, const Historico &b){
    return a.pontuacao > b.pontuacao;
}

static void merge(Vec<Historico> &v, Vec<Historico> &aux, int ini, int meio, int fim){
    int i = ini;         
    int j = meio + 1;    
    int k = ini;         

    while (i <= meio && j <= fim) {
       
        if (vemAntes(v.arr[j], v.arr[i])) 
            aux.arr[k++] = v.arr[j++];
        else
            aux.arr[k++] = v.arr[i++];
    }
    while (i <= meio) aux.arr[k++] = v.arr[i++];
    while (j <= fim) aux.arr[k++] = v.arr[j++];

    for (k = ini; k <= fim; k++)
        v.arr[k] = aux.arr[k];
}

static void mergeSortRec(Vec<Historico> &v, Vec<Historico> &aux, int ini, int fim){
    if (ini >= fim) return;
    int meio = (ini + fim) / 2;
    mergeSortRec(v, aux, ini, meio);
    mergeSortRec(v, aux, meio + 1, fim);
    merge(v, aux, ini, meio, fim);
}

void mergeSort(Vec<Historico> &v){
    if (v.tam < 2) return;
    Vec<Historico> aux(v.tam);
    mergeSortRec(v, aux, 0, (int)v.tam - 1);
}