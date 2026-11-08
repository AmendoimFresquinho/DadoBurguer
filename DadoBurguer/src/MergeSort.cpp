#include <vector>
#include "Structs.hpp"

static bool vemAntes(const Historico &a, const Historico &b){
    return a.pontuacao > b.pontuacao;
}

static void merge(std::vector<Historico> &v, std::vector<Historico> &aux, int ini, int meio, int fim){
    int i = ini;         
    int j = meio + 1;    
    int k = ini;         

    while (i <= meio && j <= fim) {
       
        if (vemAntes(v[j], v[i])) 
            aux[k++] = v[j++];
        else
            aux[k++] = v[i++];
    }
    while (i <= meio) aux[k++] = v[i++];
    while (j <= fim) aux[k++] = v[j++];

    for (k = ini; k <= fim; k++)
        v[k] = aux[k];
}

static void mergeSortRec(std::vector<Historico> &v, std::vector<Historico> &aux, int ini, int fim){
    if (ini >= fim) return;
    int meio = (ini + fim) / 2;
    mergeSortRec(v, aux, ini, meio);
    mergeSortRec(v, aux, meio + 1, fim);
    merge(v, aux, ini, meio, fim);
}

void mergeSort(std::vector<Historico> &v){
    if (v.size() < 2) return;
    std::vector<Historico> aux(v.size());
    mergeSortRec(v, aux, 0, (int)v.size() - 1);
}