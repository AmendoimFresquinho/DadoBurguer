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

Bloco CriarBloco(Rectangle ret, const char* nome, const char* arquivoTextura, Color corReserva, bool interagivel, Acoes acao) {
    Bloco b;
    b.rect = ret;
    b.nome = nome;
    b.textura = Texture2D();   
    if (arquivoTextura != nullptr && FileExists(arquivoTextura)) 
        b.textura = LoadTexture(arquivoTextura);
    
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

    const float xFina = 617.0f;
    paredes.push_back({ xFina, ESPESSURA, ESPESSURA_FINA, 196 });                    
    paredes.push_back({ xFina, 398, ESPESSURA_FINA, ALTURA - ESPESSURA - 398 });          

    blocos.push_back(CriarBloco({ 190, ESPESSURA, 88, 72 }, "Estoque", "DadoBurguer/assets/estoque.png", RED, true, ACAO_ABRIR_ESTOQUE));

    for (int i = 0; i < 3; i++) 
        blocos.push_back(CriarBloco({ ESPESSURA - 12, 100.0f + 80.0f * i, 76, 88 }, "Gabinete", "DadoBurguer/assets/gabinete.png", BROWN, false, SEM_ACAO));
    
    blocos.push_back(CriarBloco({ ESPESSURA, 386, 60, 88 }, "Geladeira", "DadoBurguer/assets/geladeira.png", SKYBLUE, true, ACAO_ABRIR_GELADEIRA));
    
    blocos.push_back(CriarBloco({ ESPESSURA - 15, 504, 90, 110 }, "Fogao", "DadoBurguer/assets/fogao.png", DARKGRAY, true, ABRIR_FOGAO));

    blocos.push_back(CriarBloco({ 184, 620, 152, 68 }, "Mesa de corte", "DadoBurguer/assets/mesa_corte.png", ORANGE, true, ACAO_CORTAR));

    blocos.push_back(CriarBloco({ xFina + ESPESSURA_FINA / 2 - 58, 228, 116, 170 }, "Atendimento", "DadoBurguer/assets/balcao.png", BEIGE, true, ACAO_ATENDER));
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

// FOGAO

TelaFogao CriarTelaFogao(float largura, float altura) {
    TelaFogao t;
    t.painel = { 80, (altura - 500) / 2, largura - 160, 500 };
    t.xDivisoria = t.painel.x + t.painel.width * 0.52f;
 
    const float pad = 28.0f;   
 
    Rectangle zonaEsq = { t.painel.x + pad, t.painel.y + pad, (t.xDivisoria - t.painel.x) - 2 * pad, t.painel.height - 2 * pad };
    Rectangle zonaDir = { t.xDivisoria + pad, t.painel.y + pad, (t.painel.x + t.painel.width - t.xDivisoria) - 2 * pad, t.painel.height - 2 * pad };
 
    t.bocas = GerarGrade(zonaEsq, 2, 2, 24.0f);
    t.slots = GerarGrade(zonaDir, 3, 3, 18.0f);
 
    t.bocaHover = -1;
    t.slotHover = -1;
    return t;
}

bool AtualizarTelaFogao(TelaFogao& tela) {
    Vector2 mouse = GetMousePosition();
 
    tela.bocaHover = -1;
    for (size_t i = 0; i < tela.bocas.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.bocas[i])) tela.bocaHover = (int)i;
    }
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slots.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slots[i])) tela.slotHover = (int)i;
    }
  
    return IsKeyPressed(KEY_E);
}

void DesenharPlaceholder(Rectangle r, Color cor) {
    DrawRectangleLinesEx(r, 3, cor);
    DrawLineEx({ r.x, r.y }, { r.x + r.width, r.y + r.height }, 3, cor);
    DrawLineEx({ r.x + r.width, r.y }, { r.x, r.y + r.height }, 3, cor);
}
 
void DesenharTelaFogao(const TelaFogao& tela) {

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 160 });
 
    DrawRectangleRec(tela.painel, RAYWHITE);
    DrawRectangleLinesEx(tela.painel, 3, BLACK);
    DrawLineEx({ tela.xDivisoria, tela.painel.y }, { tela.xDivisoria, tela.painel.y + tela.painel.height }, 3, GRAY);
 
    for (size_t i = 0; i < tela.bocas.size(); i++) {
        const Rectangle& b = tela.bocas[i];
        DesenharPlaceholder(b, BLACK);
 
        Vector2 centro = { b.x + b.width / 2, b.y + b.height / 2 };
        float menorLado = (b.width < b.height) ? b.width : b.height;
        float raio = menorLado * 0.4f;
        DrawCircleV(centro, raio, RAYWHITE);
        DrawRing(centro, raio - 3, raio, 0, 360, 48, GRAY);
 
        if ((int)i == tela.bocaHover) {
            DrawRectangleRec(b, Color{ 255, 200, 0, 60 });
            DrawRing(centro, raio - 3, raio, 0, 360, 48, ORANGE);
        }
    }
 
    for (size_t i = 0; i < tela.slots.size(); i++) {
        const Rectangle& s = tela.slots[i];
        if ((int)i == tela.slotHover) DrawRectangleRec(s, Color{ 255, 200, 0, 60 });
        DrawRectangleLinesEx(s, 3, ((int)i == tela.slotHover) ? ORANGE : GRAY);
    }
 
    DrawText("FOGAO", (int)tela.painel.x, (int)tela.painel.y - 40, 30, WHITE);
    DrawText("[E] para fechar", (int)tela.painel.x, (int)(tela.painel.y + tela.painel.height) + 14, 20, WHITE);
}