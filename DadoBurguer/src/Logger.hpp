#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

enum LogMode {
    GENERICO,
    HISTORICO_LOG
};

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
    int escreverLogAcesso(std::fstream& f, double t_merge = 0.0f, double t_radix = 0.0f);
};
struct _hash {
    int tamanho;
    int ocupadas;
    int hits;
    int misses;
    int colisoes;

    _hash() : tamanho(0), ocupadas(0), hits(0), misses(0), colisoes(0) {};
    int escreverLog(std::fstream& f);
};

struct Log {
    int logId;
    std::string logFolder;
    std::string fullPath;
    std::chrono::steady_clock::time_point timer;
    _avl AVL;
    _hist HISTORICO;
    _hash HASH;
    std::fstream file;
    LogMode modo;
    

    Log() : logId(0), logFolder("DadoBurguer/logs"), AVL(), HISTORICO(), HASH() {
        modo = GENERICO;
        fullPath = logFolder + "/log" + std::to_string(logId) + ".log";
        file.open(fullPath, std::ios::out);

        if (!file.is_open()) std::cerr << "Erro ao abrir arquivo de log '" << fullPath << "'\n";
        else file << "=== RELATÓRIO DE DESEMPENHO ===\n\n";

        if (!file) std::cerr << "Erro ao escreve header de log '" << fullPath << "'\n";
    };
    Log(LogMode m) {
        modo = m;
        switch (m){
            case LogMode::HISTORICO_LOG:
                logId = 0;
                logFolder = "DadoBurguer/logs";
                AVL = _avl();
                HISTORICO = _hist();
                HASH = _hash();
                break;

            case LogMode::GENERICO:
            default:
                Log();
                break;
        }
    };

    ~Log(){
        if (file.is_open()) {
            switch (modo) {
                case LogMode::HISTORICO_LOG:
                    break;
                
                case LogMode::GENERICO:
                default:
                    AVL.escreverLogPartida(file);
                    HASH.escreverLog(file);
                    file << "================================";
                    break;
            }
            file.close();
        }
    };
    void innit();
    double stop();

    void openLog();
    void closeLog();
};