#include "raylib.h"
#include "raymath.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>
#include <iostream>

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

void DesenharIconeNoSlotFogao(Texture2D tex, Rectangle area) {
    if (tex.id == 0) return;   // textura não carregada: não desenha nada
 
    float lado = (area.width < area.height) ? area.width : area.height;
    int escala = (int)(lado / tex.width);
    if (escala < 1) escala = 1;
 
    float larg = (float)(tex.width * escala);
    float alt = (float)(tex.height * escala);
    Rectangle origem = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle destino = { area.x + (area.width - larg) / 2, area.y + (area.height - alt) / 2, larg, alt };
    DrawTexturePro(tex, origem, destino, { 0, 6 }, 0.0f, WHITE);
}
 
void DesenharTelaFogao(const TelaFogao& tela, ListaContiguaINV &inv) {

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
 
    for (size_t i = 0; i < inv.tamanho; i++) {
        const Rectangle& s = tela.slots[i];
        Rectangle iconeInv = { s.x, s.y, s.width, s.width };   
        DesenharIconeNoSlotFogao(acessar(inv, i).textura, iconeInv);
    }

    DrawText("FOGAO", (int)tela.painel.x, (int)tela.painel.y - 40, 30, WHITE);
    DrawText("[E] para fechar", (int)tela.painel.x, (int)(tela.painel.y + tela.painel.height) + 14, 20, WHITE);
}

