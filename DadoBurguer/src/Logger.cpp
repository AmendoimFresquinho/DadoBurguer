#include "Logger.hpp"

void Log::innit(){
    timer = std::chrono::steady_clock::now();
}
double Log::stop(){
    auto fim = std ::chrono::steady_clock::now();
    return std::chrono::duration<double>(fim - timer).count();
}


int _avl::escreverLog(std::fstream& f){
    f
    << "-- AVL: Carregamento --\n"
    << "Nós inseridos: \t\t\t" << std::to_string(nInseridos) << "\n"
    << "Altura resultante: \t\t" << std::to_string(alturaTotal) << "\n"
    << "Rotações (inserção): \t" << std::to_string(nRotacoes) << "\n"
    << "Tempo de Carregamento: \t" << std::to_string(tempoDeCarregamento) << "s\n\n";

    if (!f) {std::cerr << "Erro ao escrever log\n"; return 1;}

    f.flush();
    return 0;
};
int _avl::escreverLogPartida(std::fstream& f){
    f
    << "-- AVL: buscas durante a partida --\n"
    << "Total de Buscas: \t\t\t" << std::to_string(nBuscas) << "\n"
    << "Total de Comparações: \t\t" << std::to_string(nComparacoes) << "\n"
    << "Média de comparações por busca: \t" << std::to_string((double) nComparacoes / nBuscas) << "\n"
    << "Tempo total acumulado: \t" << std::to_string(tempoTotalAcumulado) << "s\n\n";

    if (!f) {std::cerr << "Erro ao escrever log\n"; return 1;}

    f.flush();
    return 0;
};

int _hist::escreverLog(std::fstream& f){
    f
    << "-- Histórico: Carregamento --\n"
    << "Entradas Carregadas: \t\t" << std::to_string(nEntradas) <<"\n\n";

    if (!f) {std::cerr << "Erro ao escrever log\n"; return 1;}

    f.flush();
    return 0;
};

int _hash::escreverLog(std::fstream& f){
    f
    << "-- Tabela hash --\n"
    << "Tamanho (m): \t\t\t\t\t" << std::to_string(tamanho) <<"\n"
    << "Entradas ocupadas (n): \t\t\t" << std::to_string(ocupadas)<<"\n"
    << "Fator de carga (lambda):\t\t" << std::to_string((double) ocupadas/tamanho)<<"\n"
    << "Total de Hits: \t\t\t\t" << std::to_string(hits)<<"\n"
    << "Total de Misses: \t\t\t" << std::to_string(misses)<<"\n"
    << "Taxa de acerto: \t\t\t" << std::to_string((double) hits / (hits+misses)) << "\n"
    << "Total de Colisões: \t\t\t" << std::to_string(colisoes) <<"\n\n";

    if (!f) {std::cerr << "Erro ao escrever log\n"; return 1;}

    f.flush();
    return 0;
}

int _hist::escreverLogAcesso(std::fstream& f, double t_merge, double t_radix){
    f << "Tamanho: " << std::to_string(nEntradas) << " entradas\n\n";

    if (t_merge > 0)
        f << "MergeSort: " << std::to_string(t_merge) << "s\n";
    if (t_radix > 0)
        f << "RadixSort: " << std::to_string(t_radix) << "s\n";

    f << "-=-=-=-=-=-=-=-=-=-=-=-\n";

    if (!f) {std::cerr << "Erro ao escrever log\n"; return 1;}

    f.flush();
    return 0;
}

void Log::openLog(){
    switch(modo){
        case LogMode::HISTORICO_LOG:
            fullPath = logFolder + "/hist" + std::to_string(logId) + ".log";
            file.open(fullPath, std::ios::out);

            file << "=== RELATÓRIO HISTÓRICO ("<< std::to_string(logId) <<") ===\n\n";
            if (!file) std::cerr << "Erro ao escreve header de log '" << fullPath << "'\n";


            if (!file.is_open()) std::cerr << "Erro ao abrir arquivo de log '" << fullPath << "'\n";
            break;

        case LogMode::GENERICO:
        default:
            std::cout << "Essa _feature_ só funciona para logs do tipo HISTORICO.";
            break;
    }
}
void Log::closeLog(){
    switch(modo){
        case LogMode::HISTORICO_LOG:
            logId++;
            file.close();
            break;

        case LogMode::GENERICO:
        default:
            if (file.is_open()) {
                if (!AVL.escreverLogPartida(file)) std::cout << "Erro ao escrever LOG de partida da AVL" << "\n";
                if (!HASH.escreverLog(file)) std::cout << "Erro ao escrever LOG de partida da HASH" << "\n";
                file.close();}
            break;
    }
}