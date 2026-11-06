#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <vector>
#include <string>
#include <iostream>

const int ESTOQUE_COLUNAS = 5;
const int ESTOQUE_LINHAS = 3;
const float ESTOQUE_ICONE = 96.0f;   
const float ESTOQUE_ESPACO = 10.0f;   

TelaEstoque CriarTelaEstoque(float largura, float altura, IngredienteJogo PaoCima, IngredienteJogo PaoBaixo, IngredienteJogo Carne, IngredienteJogo QueijoSuico, IngredienteJogo Ovo, IngredienteJogo Bacon, IngredienteJogo Mostarda, IngredienteJogo Ketchup, IngredienteJogo Alface, IngredienteJogo Tomate, IngredienteJogo Cebola, IngredienteJogo Cheddar, IngredienteJogo Picles, IngredienteJogo CarneAssada, IngredienteJogo CarneQueimada) {
    TelaEstoque t;
    t.painel = { 80, (altura - 500) / 2, largura - 160, 500 };
    t.xDivisoria = t.painel.x + t.painel.width * 0.52f;
 
    const float pad = 28.0f;
    const float legenda = 34.0f;  
 
    t.zonaEsq = { t.painel.x + pad, t.painel.y + pad, (t.xDivisoria - t.painel.x) - 2 * pad, t.painel.height - 2 * pad };
    t.zonaDir = { t.xDivisoria + pad, t.painel.y + pad, (t.painel.x + t.painel.width - t.xDivisoria) - 2 * pad, t.painel.height - 2 * pad };

    IngredienteJogo Ingredientes[QUANTIDADE_INGREDIENTES + 1] = {PaoCima, PaoBaixo, Carne, QueijoSuico, Cheddar, Alface, Ketchup, Mostarda, Picles, Cebola, Tomate, Ovo, Bacon, CarneAssada, CarneQueimada};
 
    for (int i = 0; i < QUANTIDADE_INGREDIENTES + 1; i++) {
        t.ingredientes.push_back({ Ingredientes[i].codigo, Ingredientes[i].ehPerecivel, Ingredientes[i].textura, Ingredientes[i].nome, Ingredientes[i].turnoEstraga });
    }
 
    float larguraGrade = ESTOQUE_COLUNAS * ESTOQUE_ICONE + (ESTOQUE_COLUNAS - 1) * ESTOQUE_ESPACO;
    Rectangle gradeEsq = { t.zonaEsq.x + (t.zonaEsq.width - larguraGrade) / 2, t.zonaEsq.y + legenda, larguraGrade, t.zonaEsq.height - legenda };
    std::vector<Rectangle> todas = GerarGrade(gradeEsq, ESTOQUE_COLUNAS, ESTOQUE_LINHAS, ESTOQUE_ESPACO);
    for (size_t i = 0; i < t.ingredientes.size() - 1 && i < todas.size(); i++) {
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

bool AtualizarTelaEstoque(TelaEstoque& tela, char& escolhidoEST, int& escolhidoINV) {
    escolhidoEST = '\0';
    escolhidoINV = -1;
    Vector2 mouse = GetMousePosition();
 
    tela.ingredienteHover = -1;
    for (size_t i = 0; i < tela.celulas.size() - 2; i++) {
        if (CheckCollisionPointRec(mouse, tela.celulas[i])) tela.ingredienteHover = (int)i;
    }
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slotsInventario.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slotsInventario[i])) {
            tela.slotHover = (int)i;
        }
    }
 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tela.ingredienteHover >= 0) {
        escolhidoEST = tela.ingredientes[tela.ingredienteHover].codigo;
    }
   
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tela.slotHover >= 0) {
        escolhidoINV = tela.slotHover;
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
        } 
        return;
    }
}
 
void DesenharTelaEstoque(const TelaEstoque& tela, ListaContiguaINV &inventario) {
    
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 160 });
    DrawRectangleRec(tela.painel, RAYWHITE);
    DrawRectangleLinesEx(tela.painel, 3, BLACK);
    DrawLineEx({ tela.xDivisoria, tela.painel.y }, { tela.xDivisoria, tela.painel.y + tela.painel.height }, 3, GRAY);
 
    DrawText("INGREDIENTES", (int)tela.zonaEsq.x, (int)tela.zonaEsq.y + 2, 22, DARKGRAY);
    DrawText("INVENTARIO", (int)tela.zonaDir.x, (int)tela.zonaDir.y + 2, 22, DARKGRAY);
 
    for (size_t i = 0; i < tela.celulas.size() - 1; i++) {
        const Rectangle& c = tela.celulas[i];
        const IngredienteJogo& ing = tela.ingredientes[i];
        bool hover = ((int)i == tela.ingredienteHover);
 
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

        Rectangle iconeInv = { s.x, s.y, s.width, s.width };   
        DesenharIngrediente(tela, acessar(inventario, i).codigo, iconeInv);
    }
 
    DrawText("ESTOQUE", (int)tela.painel.x, (int)tela.painel.y - 40, 30, WHITE);
    DrawText("Clique em um ingrediente para pegar / [E] para fechar", (int)tela.painel.x, (int)(tela.painel.y + tela.painel.height) + 14, 20, WHITE);

    if (tela.slotHover >= 0 && tamanho(inventario) > tela.slotHover) {
        DesenharDicaMouse("Clique para remover", inventario, tela.slotHover);
    }
}

void DesenharDicaMouse(const char* texto, ListaContiguaINV &inventario, int escolhido) {
    const int tam = 18;
    int larg = MeasureText(texto, tam);

    Vector2 m = GetMousePosition();

    float x = m.x + 16;      
    float y = m.y + 20;

    if (x + larg + 16 > GetScreenWidth()) x = m.x - larg - 24;
    if (y + 28 > GetScreenHeight()) y = m.y - 36;

    if(acessar(inventario, escolhido).ehPerecivel){
        DrawRectangleRounded({ x, y, (float)larg + 16, 46 }, 0.4f, 6, Color{ 40, 28, 22, 230 });
        DrawText(texto, (int)x + 8, (int)y + 5, tam, RED);
        DrawText("Turno que vence:" , (int)x + 8, (int)y + 25, tam, WHITE);
        DrawText(TextFormat("%d", acessar(inventario, escolhido).turnoEstraga), (int)x + MeasureText("Turno que vence:", tam) + 15, (int)y + 25, tam, RED);
    }
    else{
        DrawRectangleRounded({ x, y, (float)larg + 16, 28 }, 0.4f, 6, Color{ 40, 28, 22, 230 });
        DrawText(texto, (int)x + 8, (int)y + 5, tam, RED);
    }
}