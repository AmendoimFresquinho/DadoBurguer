#pragma once

template <typename T>
struct Vec {
    T* arr; // Ponteiro para o primeiro elemento do vetor
    int tam; // Tamanho do vetor
    int cap; // Capacidade máxima do vetor


    Vec() {
        arr = new T[1];
        cap = 1;
        tam = 0;
    }
    Vec(int n) {
        cap = n;
        arr = new T[n];
        tam = 0;        
    }
    ~Vec() {
        delete[] arr;
    }

    void push(T dado){
        if (tam == cap) {
            T* tmp = new T[cap*2];

            for (int i = 0; i < cap; i++){
                tmp[i] = arr[i];
            }

            delete[] arr;

            arr = tmp;
            cap *= 2;
        };

        arr[tam] = dado;
        tam++;
    };

    void pop() {
        if (tam > 0) tam--;
    }

    T get(int index){
        if (index >= 0 && index < tam) return arr[index];

        return T(); // Se não está nos limites, retorna o default
    }

    void wipe() {
        for (int i = 0; i < tam; i++){
            arr[i] = T();
        }

        tam = 0;
    }
    void resize(){
        cap = tam;
    }
    void resize(int t){
        if (t >= tam){
            cap = t;
        }
    }
};