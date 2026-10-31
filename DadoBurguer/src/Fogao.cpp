#include "raylib.h"
#include <cmath>
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

bool AtualizarTelaFogao(TelaFogao& tela, int &escolhidoFogInv, int &escolhidoFogBoc, ListaContiguaINV &inventario) {
    Vector2 mouse = GetMousePosition();
 
    tela.bocaHover = -1;
    for (size_t i = 0; i < tela.bocas.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.bocas[i])) tela.bocaHover = (int)i;
    }
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slots.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slots[i])) tela.slotHover = (int)i;
    }

    escolhidoFogInv = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && acessar(inventario, tela.slotHover).nome == "Carne" ? tela.slotHover : -1;

    escolhidoFogBoc = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tela.carnes.tamanho < 4 ? tela.bocaHover : -1;

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

static bool ehCarne(const IngredienteJogo &ing) {
    return ing.codigo == 'c';
}

// SEU: como a carne muda de acordo com o caractere
static void desenhaCarne(char c, Vector2 centro, const Texture2D &texCarne, float escala) {
    Color tint = WHITE;

    switch (c) {
        case 'c':  tint = WHITE;  break;
        case 'a':  tint = BROWN;  break;
        case 'q':  tint = BLACK;  break;
        default:   break;
    }

    Vector2 pos = { centro.x - texCarne.width  * escala / 2.0f, centro.y - texCarne.height * escala / 2.0f };
    DrawTextureEx(texCarne, pos, 0.0f, escala, tint);
}

void desenhaPanelas(ListaContiguaINV &fogao, const std :: vector<Rectangle> &bocas, const Texture2D &texPanela, const Texture2D &texCarne, const Texture2D &texFogo) {
    const float escalaPanela = 1.4f;  
    const float escalaCarne = 2.0f; 
    const float escalaFogo = 1.0f + 0.03f * sinf(GetTime() * 8.0f);
 
    for (int i = 0; i < fogao.tamanho && i < (int)bocas.size(); i++) {        
            
        IngredienteJogo *ing = enderecoDe(fogao, i);
        if (ing == nullptr) continue;

        Vector2 centro = { bocas[i].x + bocas[i].width  / 2.0f, bocas[i].y + bocas[i].height / 2.0f };

        Vector2 posFogo = { centro.x - texFogo.width  * escalaFogo / 2.0f, centro.y - texFogo.height * escalaFogo / 2.0f };
        DrawTextureEx(texFogo, posFogo, 0.0f, escalaFogo, WHITE);

        Vector2 posPanela = { centro.x - texPanela.width  * escalaPanela / 2.0f, centro.y - texPanela.height * escalaPanela / 2.0f };
        DrawTextureEx(texPanela, posPanela, 0.0f, escalaPanela, WHITE);

        desenhaCarne(ing->codigo, centro, texCarne, escalaCarne);
    }
}