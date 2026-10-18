#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include "ingredientes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>
#include <stddef.h> 

const int ESTOQUE_COLUNAS = 5;
const int ESTOQUE_LINHAS = 3;
const float ESTOQUE_ICONE = 96.0f;   
const float ESTOQUE_ESPACO = 10.0f;   

TelaEstoque CriarTelaEstoque(float largura, float altura) {
    TelaEstoque t;
    t.painel = { 80, (altura - 500) / 2, largura - 160, 500 };
    t.xDivisoria = t.painel.x + t.painel.width * 0.52f;
 
    const float pad = 28.0f;
    const float legenda = 34.0f;  
 
    t.zonaEsq = { t.painel.x + pad, t.painel.y + pad, (t.xDivisoria - t.painel.x) - 2 * pad, t.painel.height - 2 * pad };
    t.zonaDir = { t.xDivisoria + pad, t.painel.y + pad, (t.painel.x + t.painel.width - t.xDivisoria) - 2 * pad, t.painel.height - 2 * pad };

    Texture2D paoCima = LoadTexture("DadoBurguer/assets/INV/cima_pao_inventario.png");
    Texture2D paoBaixo = LoadTexture("DadoBurguer/assets/INV/baixo_pao_inventario.png");
    Texture2D cheddar = LoadTexture("DadoBurguer/assets/INV/cheddar_inventario.png");
    Texture2D suico = LoadTexture("DadoBurguer/assets/INV/suico_inventario.png");
    Texture2D carne_crua = LoadTexture("DadoBurguer/assets/INV/carne_crua_inventario.png");
    Texture2D alface = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D tomate = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D ketchup = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D mostarda = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D cebola = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D ovo = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D bacon = LoadTexture("DadoBurguer/assets/INV/plisno.png");
    Texture2D picles = LoadTexture("DadoBurguer/assets/INV/plisno.png");

    IngredienteJogo Pao_cima = { 'z', false, paoCima, "Pao de Cima", 0 };
    IngredienteJogo Pao_baixo ={ 'x', false, paoBaixo, "Pao de Baixo", 0 };
    IngredienteJogo Carne = { 'n', true, carne_crua, "Carne", VALIDADE };
    IngredienteJogo Queijo_Suico = { 's', true, suico, "Suico", VALIDADE };
    IngredienteJogo Cheddar = { 'q', true, cheddar, "Cheddar", VALIDADE };
    IngredienteJogo Alface = { 'a', false, alface, "Alface", 0};
    IngredienteJogo Ketchup = { 'k', false, ketchup, "Ketchup", 0};
    IngredienteJogo Mostarda = { 'm', false, mostarda, "Mostarda", 0};
    IngredienteJogo Picles = { 'p', false, picles, "Picles", 0};
    IngredienteJogo Cebola = { 'c', false, cebola, "Cebola", 0};
    IngredienteJogo Tomate = { 't', false, tomate, "Tomate", 0};
    IngredienteJogo Ovo = { 'o', false, ovo, "Ovo", 0};
    IngredienteJogo Bacon = { 'b', false, bacon, "Bacon", 0};
    
    IngredienteJogo Ingredientes[QUANTIDADE_INGREDIENTES] = {Pao_cima, Pao_baixo, Carne, Queijo_Suico, Cheddar, Alface, Ketchup, Mostarda, Picles, Cebola, Tomate, Ovo, Bacon};
 
    for (int i = 0; i < QUANTIDADE_INGREDIENTES; i++) {
        t.ingredientes.push_back({ Ingredientes[i].codigo, Ingredientes[i].ehPerecivel, Ingredientes[i].textura, Ingredientes[i].nome, Ingredientes[i].turnoEstraga });
    }
 
    float larguraGrade = ESTOQUE_COLUNAS * ESTOQUE_ICONE + (ESTOQUE_COLUNAS - 1) * ESTOQUE_ESPACO;
    Rectangle gradeEsq = { t.zonaEsq.x + (t.zonaEsq.width - larguraGrade) / 2, t.zonaEsq.y + legenda, larguraGrade, t.zonaEsq.height - legenda };
    std::vector<Rectangle> todas = GerarGrade(gradeEsq, ESTOQUE_COLUNAS, ESTOQUE_LINHAS, ESTOQUE_ESPACO);
    for (size_t i = 0; i < t.ingredientes.size() && i < todas.size(); i++) {
        t.celulas.push_back(todas[i]);
    }
 
    const float lado = 3 * 120.0f + 2 * 14.0f;  
    Rectangle gradeDir = { t.zonaDir.x + (t.zonaDir.width - lado) / 2, t.zonaDir.y + legenda + (t.zonaDir.height - legenda - lado) / 2, lado, lado };
    t.slotsInventario = GerarGrade(gradeDir, 3, 3, 14.0f);
 
    t.ingredienteHover = -1;
    t.slotHover = -1;
    return t;
}
 
void DescarregarTelaEstoque(TelaEstoque& t) {
    for (size_t i = 0; i < t.ingredientes.size(); i++) {
        if (t.ingredientes[i].textura.id != 0) UnloadTexture(t.ingredientes[i].textura);
    }
}

bool AtualizarTelaEstoque(TelaEstoque& tela, char& escolhido) {
    escolhido = '\0';
    Vector2 mouse = GetMousePosition();
 
    tela.ingredienteHover = -1;
    for (size_t i = 0; i < tela.celulas.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.celulas[i])) tela.ingredienteHover = (int)i;
    }
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slotsInventario.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slotsInventario[i])) tela.slotHover = (int)i;
    }
 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tela.ingredienteHover >= 0) {
        escolhido = tela.ingredientes[tela.ingredienteHover].codigo;
    }
 
    return IsKeyPressed(KEY_E);
}

void DesenharIngrediente(const TelaEstoque& tela, char codigo, Rectangle area) {
    float lado = (area.width < area.height) ? area.width : area.height;
 
    for (size_t i = 0; i < tela.ingredientes.size(); i++) {
        const IngredienteJogo& ing = tela.ingredientes[i];
        if (ing.codigo != codigo) continue;
 
        if (ing.textura.id != 0) {
            int escala = (int)(lado / ing.textura.width);
            if (escala < 1) escala = 1;
            float larg = (float)(ing.textura.width * escala);
            float alt = (float)(ing.textura.height * escala);
            Rectangle origem = { 0, 0, (float)ing.textura.width, (float)ing.textura.height };
            Rectangle destino = { area.x + (area.width - larg) / 2, area.y + (area.height - alt) / 2, larg, alt };
            DrawTexturePro(ing.textura, origem, destino, { 0, 0 }, 0.0f, WHITE);
        } else {
            Rectangle q = { area.x + (area.width - lado) / 2, area.y + (area.height - lado) / 2, lado, lado };
            DesenharPlaceholder(q, DARKGRAY);
            const char* letra = TextFormat("%c", codigo);
            int larg = MeasureText(letra, 32);
            int cx = (int)(q.x + lado / 2);
            int cy = (int)(q.y + lado / 2);
            DrawRectangle(cx - larg / 2 - 6, cy - 20, larg + 12, 40, RAYWHITE);
            DrawText(letra, cx - larg / 2, cy - 16, 32, DARKGRAY);
        }
        return;
    }
}
 
void DesenharTelaEstoque(const TelaEstoque& tela) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 160 });
 
    DrawRectangleRec(tela.painel, RAYWHITE);
    DrawRectangleLinesEx(tela.painel, 3, BLACK);
    DrawLineEx({ tela.xDivisoria, tela.painel.y }, { tela.xDivisoria, tela.painel.y + tela.painel.height }, 3, GRAY);
 
    DrawText("INGREDIENTES", (int)tela.zonaEsq.x, (int)tela.zonaEsq.y + 2, 22, DARKGRAY);
    DrawText("INVENTARIO", (int)tela.zonaDir.x, (int)tela.zonaDir.y + 2, 22, DARKGRAY);
 
    for (size_t i = 0; i < tela.celulas.size(); i++) {
        const Rectangle& c = tela.celulas[i];
        const IngredienteJogo& ing = tela.ingredientes[i];
        bool hover = ((int)i == tela.ingredienteHover);
 
        // Moldura por FORA da célula, para o ícone ocupar os 96 px inteiros
        Rectangle moldura = { c.x - 3, c.y - 3, c.width + 6, c.height + 6 };
        if (hover) DrawRectangleRec(moldura, Color{ 255, 200, 0, 60 });
        DrawRectangleLinesEx(moldura, 3, hover ? ORANGE : GRAY);
 
        Rectangle icone = { c.x, c.y, c.width, c.width };   
        DesenharIngrediente(tela, ing.codigo, icone);
 
        int larg = ing.nome.size();
        DrawText(ing.nome.c_str(), (int)(c.x + (c.width - larg) / 12), (int)(c.y + c.width + 8), 14, BLACK);
    }
 
    for (size_t i = 0; i < tela.slotsInventario.size(); i++) {
        const Rectangle& s = tela.slotsInventario[i];
        bool hover = ((int)i == tela.slotHover);
        if (hover) DrawRectangleRec(s, Color{ 255, 200, 0, 60 });
        DrawRectangleLinesEx(s, 3, hover ? ORANGE : GRAY);
    }
 
    DrawText("ESTOQUE", (int)tela.painel.x, (int)tela.painel.y - 40, 30, WHITE);
    DrawText("Clique em um ingrediente para pegar / [E] para fechar", (int)tela.painel.x, (int)(tela.painel.y + tela.painel.height) + 14, 20, WHITE);
}
