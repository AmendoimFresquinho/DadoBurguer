#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

struct _avl {
    int nInseridos;
    int alturaTotal;
    int nRotacoes;
    double tempoDeCarregamento;
    int nBuscas;
    int nComparacoes;
    double tempoTotalAcumulado;

    _avl() : nInseridos(0), alturaTotal(0), nRotacoes(0), tempoDeCarregamento(0.0f), nBuscas(0), nComparacoes(0), tempoTotalAcumulado(0.0f) {};
    int escreverLog(std::fstream& f);
    int escreverLogPartida(std::fstream& f);
};
struct _hist {
    int nEntradas;

    _hist(): nEntradas(0) {};
    int escreverLog(std::fstream& f);
};


struct Log {
    int logId;
    std::string logFolder;
    std::string fullPath;
    std::chrono::steady_clock::time_point timer;
    _avl AVL;
    _hist HISTORICO;
    std::fstream file;
    

    Log() : logId(0), logFolder("DadoBurguer/logs"), AVL(), HISTORICO() {
        fullPath = logFolder + "/log" + std::to_string(logId) + ".txt";
        file.open(fullPath, std::ios::out);

        if (!file.is_open()) std::cerr << "Erro ao abrir arquivo de log '" << fullPath << "'\n";
        else file << "=== RELATÓRIO DE DESEMPENHO ===\n\n";

        if (!file) std::cerr << "Erro ao escreve header de log '" << fullPath << "'\n";
    };

    ~Log(){
        if (file.is_open()) {
            AVL.escreverLogPartida(file);
            file.close();
        }
    };
    void innit();
    double stop();
};