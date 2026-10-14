#include "raylib.h"
#include "raymath.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <cfloat>
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

void MostrarMensagem(EstadoJogo& estado, const char* texto) {
    estado.mensagem = texto;
    estado.tempoMensagem = 2.0f;
}

// Cria um bloco; se o arquivo de textura existir, carrega. Senão usa a cor.
Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao) {
    Bloco b;
    b.rect = ret;
    b.nome = nome;
    b.textura = Texture2D();   // zerada: id == 0
    if (arquivoTextura != nullptr && FileExists(arquivoTextura)) {
        b.textura = LoadTexture(arquivoTextura);
    }
    b.cor = corReserva;
    b.interage = interagivel;
    b.acao = acao;
    return b;
}

void ConstruirMapa(std::vector<Rectangle>& paredes, std::vector<Bloco>& blocos) {

    paredes.push_back({ 0, 0, LARGURA, ESPESSURA });              
    paredes.push_back({ 0, ALTURA - ESPESSURA, LARGURA, ESPESSURA });           
    paredes.push_back({ 0, ESPESSURA, ESPESSURA, ALTURA - 2 * ESPESSURA });       
    paredes.push_back({ LARGURA - ESPESSURA, ESPESSURA, ESPESSURA, ALTURA - 2 * ESPESSURA });  

    // ----- Parede fina (divide cozinha e clientes) -----
    // Duas partes: acima e abaixo do balcão de atendimento (que ocupa y de 228 a 398).
    const float xFina = 617.0f;
    paredes.push_back({ xFina, ESPESSURA, ESPESSURA_FINA, 196 });                    // y: 32 -> 228
    paredes.push_back({ xFina, 398, ESPESSURA_FINA, ALTURA - ESPESSURA - 398 });          // y: 398 -> 688

    
    blocos.push_back(CriarBloco({ 190, ESPESSURA, 88, 72 }, "Estoque", "assets/estoque.png", RED, true, ACAO_ABRIR_ESTOQUE));

    for (int i = 0; i < 3; i++) {
        blocos.push_back(CriarBloco({ ESPESSURA, 146.0f + 70.0f * i, 64, 70 }, "Gabinete", "assets/gabinete.png", BROWN, false, SEM_ACAO));
    }

    blocos.push_back(CriarBloco({ ESPESSURA, 386, 80, 60 }, "Geladeira", "assets/geladeira.png", SKYBLUE, true, ACAO_ABRIR_GELADEIRA));

    blocos.push_back(CriarBloco({ ESPESSURA, 504, 68, 112 }, "Fogao", "assets/fogao.png", DARKGRAY, true, ABRIR_FOGAO));

    blocos.push_back(CriarBloco({ 184, 620, 152, 68 }, "Mesa de corte", "assets/mesa_corte.png", ORANGE, true, ACAO_CORTAR));

    blocos.push_back(CriarBloco({ xFina + ESPESSURA_FINA / 2 - 58, 228, 116, 170 }, "Atendimento", "assets/balcao.png", BEIGE, true, ACAO_ATENDER));
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
