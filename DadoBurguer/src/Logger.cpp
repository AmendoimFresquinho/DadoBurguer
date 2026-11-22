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