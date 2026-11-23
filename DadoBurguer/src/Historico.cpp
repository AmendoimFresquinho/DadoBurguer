#include <fstream>
#include <string>
//#include <vector>
#include "Vec.hpp"
#include "Structs.hpp"
#include "raylib.h"
#include "Funcoes.hpp"

int carregaHistorico(const std::string &nomeArquivo, Vec<Historico> &v) {

    std::ifstream arq(nomeArquivo);

    if (!arq.is_open()) 
        return -1;

    Historico h;

    while (std::getline(arq, h.nome) && (arq >> h.pontuacao)) { // Getline pq senao ele para nos espacos, ai tem que ter
        arq.ignore();            
        v.push(h);
    }
    return (int)v.tam;
}

bool salvaPontuacao(const std::string &nomeArquivo, const Historico &h) {
    bool precisaQuebra = !arquivoTerminaEmQuebra(nomeArquivo);   // ANTES de abrir para escrever
   
    std::ofstream arq(nomeArquivo, std::ios::app);

    if (!arq.is_open()) 
        return false;

    if (precisaQuebra)
        arq << "\n";  

    arq << h.nome << "\n" << h.pontuacao << "\n";
    return true;
}

bool telaDigitarNome(std::string &nome, int pontuacao) {
    const int MAX_NOME = 20;

    // 1. letras digitadas neste frame
    int c = GetCharPressed();
    while (c > 0) {
        if (c >= 32 && c <= 125 && (int)nome.size() < MAX_NOME)
            nome += (char)c;
        c = GetCharPressed();
    }

    if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !nome.empty())
        nome.pop_back();

    const char *titulo = TextFormat("%d", pontuacao);
    int tamTitulo = (int)(ALTURA * 0.07f);
    DrawText(titulo, (int)((LARGURA - MeasureText(titulo, tamTitulo)) / 2), (int)(ALTURA - 192), tamTitulo, WHITE);

    Rectangle caixa = { LARGURA * 0.275f, ALTURA * 0.48f, LARGURA * 0.45f, ALTURA * 0.11f };
    
    int tamNome = (int)(caixa.height * 0.43f);
    int xNome = (int)(caixa.x + 40);
    int yNome = (int)(5 + caixa.y + (caixa.height - tamNome) / 2);
    DrawText(nome.c_str(), xNome, yNome, tamNome, WHITE);

    // cursor piscando depois do último caractere
    if ((int)(GetTime() * 2) % 2 == 0 && nome.size() < MAX_NOME)
        DrawText("_", xNome + MeasureText(nome.c_str(), tamNome), yNome, tamNome, WHITE);

        return IsKeyPressed(KEY_ENTER) && !nome.empty();
    }

void imprimeHistorico(const Vec<Historico> &v, int quantos) { // TEMP
    std::cout << "Historico (" << v.tam << " registros)\n";

    for (int i = 0; i < (int)v.tam; i++) {
        std::cout << i + 1 << ". [" << v.arr[i].nome << "] " << v.arr[i].pontuacao << "\n";
    }
}

static bool arquivoTerminaEmQuebra(const std::string &nomeArquivo) { //Garante que nao vai dar bo no arquivo
    std::ifstream in(nomeArquivo, std::ios::binary);
    if (!in.is_open()) return true;      

    in.seekg(0, std::ios::end);
    if (in.tellg() == 0) return true;    

    in.seekg(-1, std::ios::end);         
    char c;
    in.get(c);
    return c == '\n';
}

void desenhaHistorico(const Vec<Historico>& historico) {
    const int tamanhoFonte = 20;
    const Color corTexto = { 55, 25, 10, 255 };

    // Centro vertical de cada linha da imagem.
    const int centroY[10] = {
        248, 300, 350, 399, 444,
        487, 530, 574, 617, 660
    };

    int quantidade = historico.tam;
    if (quantidade > 10)
        quantidade = 10;

    for (int i = 0; i < quantidade; i++) {
        int y = centroY[i] - tamanhoFonte / 2;

        // Limita o nome ao espaço da coluna.
        BeginScissorMode(203, y, 675, tamanhoFonte + 4);

        DrawText(
            historico.arr[i].nome.c_str(),
            205, y,
            tamanhoFonte,
            corTexto
        );

        EndScissorMode();

        std::string pontos =
            std::to_string(historico.arr[i].pontuacao);

        // Alinha a pontuação à direita do campo.
        int x = 1165 - MeasureText(pontos.c_str(), tamanhoFonte);

        DrawText(
            pontos.c_str(),
            x, y,
            tamanhoFonte,
            corTexto
        );
    }
}