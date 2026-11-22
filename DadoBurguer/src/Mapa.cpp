#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <vector>
#include <iostream>

void DrawBlock(const Bloco& b) {
    if (b.textura.id != 0) {
        Rectangle src = { 0, 0, (float)b.textura.width, (float)b.textura.height };
        DrawTexturePro(b.textura, src, b.rect, { 0, 0 }, 0.0f, WHITE);  // estica a textura no bloco
    } else {
        DrawRectangleRec(b.rect, b.cor);
        DrawRectangleLinesEx(b.rect, 2, BLACK);
    }
}

Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao, int staminaGasta) {
    Bloco b;
    b.rect = ret;
    b.nome = nome;
    b.textura = Texture2D();   
    if (arquivoTextura != nullptr && FileExists(arquivoTextura)) 
        b.textura = LoadTexture(arquivoTextura);
    
    b.cor = corReserva;
    b.interage = interagivel;
    b.acao = acao;
    b.staminaGasta = staminaGasta;
    return b;
}

void ConstruirMapa(std::vector<Rectangle>& paredes, std::vector<Bloco>& blocos) {

    paredes.push_back({ 0, 0, LARGURA, ESPESSURA });              
    paredes.push_back({ 0, ALTURA - ESPESSURA, LARGURA, ESPESSURA });           
    paredes.push_back({ 0, ESPESSURA, ESPESSURA, ALTURA - 2 * ESPESSURA });       
    paredes.push_back({ LARGURA - ESPESSURA, ESPESSURA, ESPESSURA, ALTURA - 2 * ESPESSURA });  

    const float xFina = 617.0f;
    paredes.push_back({ xFina, ESPESSURA, ESPESSURA_FINA, 196 });                    
    paredes.push_back({ xFina, 398, ESPESSURA_FINA, ALTURA - ESPESSURA - 398 });          

    for (int i = 0; i < 3; i++) 
        blocos.push_back(CriarBloco({ ESPESSURA - 12, 100.0f + 80.0f * i, 76, 88 }, "Gabinete", "DadoBurguer/assets/gabinete.png", BROWN, false, SEM_ACAO, 0));
    
    blocos.push_back(CriarBloco({ ESPESSURA, 386, 60, 88 }, "Geladeira", "DadoBurguer/assets/geladeira.png", SKYBLUE, true, ACAO_ABRIR_ESTOQUE, STAMINA_GELADEIRA));
    
    blocos.push_back(CriarBloco({ ESPESSURA - 15, 504, 90, 110 }, "Fogão", "DadoBurguer/assets/fogao.png", DARKGRAY, true, ABRIR_FOGAO, STAMINA_FOGAO));

    blocos.push_back(CriarBloco({ 184, 600, 130, 90 }, "Mesa de Corte", "DadoBurguer/assets/mesa_corte.png", ORANGE, true, ACAO_CORTAR, 0));

    blocos.push_back(CriarBloco({ xFina + ESPESSURA_FINA / 2 - 58, 228, 116, 170 }, "Atendimento", "DadoBurguer/assets/balcao.png", BEIGE, true, ACAO_ATENDER, 1));

    blocos.push_back(CriarBloco({ 484 - 100, 600, 140, 90 }, "Mesa de Montagem", "DadoBurguer/assets/mesa_montagem.png", ORANGE, true, ACAO_MONTAR, 1));

}

void DesenharBloco(const Bloco& b) {
    if (b.textura.id != 0) {
        Rectangle origem = { 0, 0, (float)b.textura.width, (float)b.textura.height };
        DrawTexturePro(b.textura, origem, b.rect, { 0, 0 }, 0.0f, WHITE);  // estica no retângulo
    } else {
        DrawRectangleRec(b.rect, b.cor);
        DrawRectangleLinesEx(b.rect, 2, BLACK);
    }
}

std::vector<Rectangle> GerarGrade(Rectangle zona, int colunas, int linhas, float espaco) {
    std::vector<Rectangle> celulas;
    float larg = (zona.width  - espaco * (colunas - 1)) / colunas;
    float alt  = (zona.height - espaco * (linhas  - 1)) / linhas;
 
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            celulas.push_back({ zona.x + c * (larg + espaco), zona.y + l * (alt + espaco), larg, alt });
        }
    }
    return celulas;
}

void DesenharEtiqueta(const char* texto, int x, int y) {
    int larg = MeasureText(texto, 20);
    DrawRectangleRounded({ (float)x - 8, (float)y - 3, (float)larg + 16, 26 }, 0.4f, 6, { 40, 28, 22, 220 });
    DrawText(texto, x, y, 20, WHITE);
}

void DesenharMundo(const Texture2D& fundo, const std::vector<Bloco>& blocos, const Jogador& jogador, const AnimJogador& anim, const Bloco* alvo, const EstadoJogo& estado, const int &turno, const int &stamina, const int &processos, const int &pontuacao) {

    Rectangle hb = HitBox(jogador);
    Rectangle sprite = { jogador.posicao.x - jogador.tamanho / 2,(jogador.posicao.y + jogador.alturaHit / 2) - jogador.tamanho, jogador.tamanho, jogador.tamanho };

    DrawTexture(fundo, 0, 0, WHITE);

    for (size_t i = 0; i < blocos.size(); i++) 
        DesenharBloco(blocos[i]);

    DesenharAnimJogador(anim, sprite);

    if (alvo != nullptr) {
        const char* texto = TextFormat("[E] %s", alvo->nome.c_str());
        int x = (int)(hb.x + hb.width / 2) - MeasureText(texto, 20) / 2;
        DesenharEtiqueta(texto, x, (int)hb.y - 34);
    }

    desenhaTurno(turno, stamina);
    desenhaProcessos(processos);
    pontos(pontuacao);

}