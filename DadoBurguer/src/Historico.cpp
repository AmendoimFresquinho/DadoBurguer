#include <fstream>
#include <string>
#include <vector>
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raylib.h"

int carregaHistorico(const std::string &nomeArquivo, std::vector<Historico> &v) {

    std::ifstream arq(nomeArquivo);

    if (!arq.is_open()) 
        return -1;

    Historico h;

    while (std::getline(arq, h.nome) && (arq >> h.pontuacao)) { // Getline pq senao ele para nos espacos, ai tem que ter
        arq.ignore();            
        v.push_back(h);
    }
    return (int)v.size();
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

    // 2. apagar (IsKeyPressedRepeat só existe no raylib 5.0+)
    if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !nome.empty())
        nome.pop_back();

    // 3. desenhar
    float L = (float)GetScreenWidth();
    float A = (float)GetScreenHeight();

    // título (centralizado)
    const char *titulo = TextFormat("Fim de jogo! Pontuacao: %d", pontuacao);
    int tamTitulo = (int)(A * 0.07f);
    DrawText(titulo, (int)((L - MeasureText(titulo, tamTitulo)) / 2), (int)(A * 0.22f), tamTitulo, BLACK);

    // instrução (centralizada)
    const char *instr = "Digite seu nome e aperte Enter:";
    int tamInstr = (int)(A * 0.045f);
    DrawText(instr, (int)((L - MeasureText(instr, tamInstr)) / 2), (int)(A * 0.38f), tamInstr, DARKGRAY);

    // caixa de texto (centralizada: 0.275 + 0.45 + 0.275 = 1)
    Rectangle caixa = { L * 0.275f, A * 0.48f, L * 0.45f, A * 0.11f };
    DrawRectangleLinesEx(caixa, 3, BLACK);

    // nome digitado, alinhado à esquerda dentro da caixa
    int tamNome = (int)(caixa.height * 0.6f);
    int xNome = (int)(caixa.x + 15);
    int yNome = (int)(caixa.y + (caixa.height - tamNome) / 2);
    DrawText(nome.c_str(), xNome, yNome, tamNome, BLACK);

    // cursor piscando depois do último caractere
    if ((int)(GetTime() * 2) % 2 == 0)
        DrawText("_", xNome + MeasureText(nome.c_str(), tamNome), yNome, tamNome, BLACK);
        // 4. confirmar
        return IsKeyPressed(KEY_ENTER) && !nome.empty();
    }

void imprimeHistorico(const std::vector<Historico> &v, int quantos) { // TEMP
    std::cout << "Historico (" << v.size() << " registros)\n";

    for (int i = 0; i < (int)v.size() && i < quantos; i++) {
        std::cout << i + 1 << ". [" << v[i].nome << "] " << v[i].pontuacao << "\n";
    }
}

static bool arquivoTerminaEmQuebra(const std::string &nomeArquivo) { //Garante que nao vai dar bo no arquivo
    std::ifstream in(nomeArquivo, std::ios::binary);
    if (!in.is_open()) return true;      // arquivo não existe: nada a quebrar

    in.seekg(0, std::ios::end);
    if (in.tellg() == 0) return true;    // arquivo vazio

    in.seekg(-1, std::ios::end);         // vai para o último caractere
    char c;
    in.get(c);
    return c == '\n';
}