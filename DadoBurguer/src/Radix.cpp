#include <string>
#include "Structs.hpp"
#include "Vec.hpp"

int chaveNome(const std::string& nome, int posicao) {
    if (posicao >= static_cast<int>(nome.size()))
        return 0;

    return static_cast<unsigned char>(nome[posicao]) + 1;
}

void countingSort(Vec<Historico>& v, int posicao, Historico* auxiliar) {
    
    int contagem[257] = {};

    // Conta as ocorrências de cada chave.
    for (int i = 0; i < v.tam; i++) {
        int chave = chaveNome(v.arr[i].nome, posicao);
        contagem[chave]++;
    }

    for (int i = 1; i < 257; i++)
        contagem[i] += contagem[i - 1];

    for (int i = v.tam - 1; i >= 0; i--) {
        int chave = chaveNome(v.arr[i].nome, posicao);

        contagem[chave]--;
        auxiliar[contagem[chave]] = v.arr[i];
    }

    for (int i = 0; i < v.tam; i++)
        v.arr[i] = auxiliar[i];
}

void radixSort(Vec<Historico>& v) {
    if (v.tam <= 1)
        return;

    int maiorNome = 0;

    for (int i = 0; i < v.tam; i++) {
        int tamanho = static_cast<int>(v.arr[i].nome.size());

        if (tamanho > maiorNome)
            maiorNome = tamanho;
    }

    Historico* auxiliar = new Historico[v.tam];

    for (int posicao = maiorNome - 1; posicao >= 0; posicao--)
        countingSort(v, posicao, auxiliar);

    delete[] auxiliar;
}