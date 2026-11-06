#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include <vector>
#include <iostream>

const bool INV_MOSTRAR_NUMEROS = true;   // número pequeno em cada slot (ajuda a testar)

void imprime(ListaContiguaINV inv){

 for (int i = 0; i < CAPACIDADE; i++) {
        std::cout << acessar(inv, i).codigo << " ";
    }
}

void adicionaNoInventario(char escolhidoEST, ListaContiguaINV &inventario, IngredienteJogo PaoCima, IngredienteJogo PaoBaixo, IngredienteJogo Carne, IngredienteJogo QueijoSuico, IngredienteJogo Ovo, IngredienteJogo Bacon, IngredienteJogo Mostarda, IngredienteJogo Ketchup, IngredienteJogo Alface, IngredienteJogo Tomate, IngredienteJogo Cebola, IngredienteJogo Cheddar, IngredienteJogo Picles ){

    if(escolhidoEST == 'z') inserir(inventario, PaoCima, tamanho(inventario));
    if(escolhidoEST == 'x') inserir(inventario, PaoBaixo, tamanho(inventario));
    if(escolhidoEST == 'n') inserir(inventario, Carne, tamanho(inventario));
    if(escolhidoEST == 's') inserir(inventario, QueijoSuico, tamanho(inventario));
    if(escolhidoEST == 'q') inserir(inventario, Cheddar, tamanho(inventario));
    if(escolhidoEST == 'a') inserir(inventario, Alface, tamanho(inventario));
    if(escolhidoEST == 'k') inserir(inventario, Ketchup, tamanho(inventario));
    if(escolhidoEST == 'm') inserir(inventario, Mostarda, tamanho(inventario));
    if(escolhidoEST == 'p') inserir(inventario, Picles, tamanho(inventario));
    if(escolhidoEST == 'c') inserir(inventario, Cebola, tamanho(inventario));
    if(escolhidoEST == 't') inserir(inventario, Tomate, tamanho(inventario));
    if(escolhidoEST == 'o') inserir(inventario, Ovo, tamanho(inventario));
    if(escolhidoEST == 'b') inserir(inventario, Bacon, tamanho(inventario));

}

void removeDoInventario(int escolhidoINV, ListaContiguaINV &inventario){
    remover(inventario, escolhidoINV);
}

TelaInventario CriarTelaInventario(float largura, float altura) {
    TelaInventario t;
 
    const float lado = 3 * 120.0f + 2 * 14.0f;    
    const float pad = 32.0f;
    const float tam = lado + 2 * pad;              
 
    t.painel = { (largura - tam) / 2, (altura - tam) / 2, tam, tam };
 
    Rectangle grade = { t.painel.x + pad, t.painel.y + pad, lado, lado };
    t.slots = GerarGrade(grade, 3, 3, 14.0f);
 
    t.slotHover = -1;
    return t;
}

bool AtualizarTelaInventario(TelaInventario& tela, int& clicado) {
    Vector2 mouse = GetMousePosition();
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slots.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slots[i])) tela.slotHover = (int)i;
    }
 
    clicado = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? tela.slotHover : -1;
 
    return IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_I);
}

void DesenharIconeNoSlot(Texture2D tex, Rectangle area) {
    if (tex.id == 0) return;   // textura não carregada: não desenha nada
 
    float lado = (area.width < area.height) ? area.width : area.height;
    int escala = (int)(lado / tex.width);
    if (escala < 1) escala = 1;
 
    float larg = (float)(tex.width * escala);
    float alt = (float)(tex.height * escala);
    Rectangle origem = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle destino = { area.x + (area.width - larg) / 2, area.y + (area.height - alt) / 2, larg, alt };
    DrawTexturePro(tex, origem, destino, { 0, 0 }, 0.0f, WHITE);
}

void DesenharTelaInventario(const TelaInventario& tela, ListaContiguaINV &inventario) {

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 160 });
    DrawRectangleRec(tela.painel, RAYWHITE);
    DrawRectangleLinesEx(tela.painel, 3, BLACK);
 
    for (size_t i = 0; i < tela.slots.size(); i++) {
        const Rectangle& s = tela.slots[i];
        bool hover = ((int)i == tela.slotHover);
 
        if (hover) DrawRectangleRec(s, Color{ 255, 200, 0, 60 });
        DrawRectangleLinesEx(s, 3, hover ? ORANGE : GRAY);
 
        if (INV_MOSTRAR_NUMEROS) {
            DrawText(TextFormat("%d", (int)i + 1), (int)s.x + 8, (int)s.y + 6, 16, LIGHTGRAY);
        }
    }

    for(int i = 0; i < inventario.tamanho; i++){ // So desenha o tamanho do vetor, senao fica bizarro
        const Rectangle& s = tela.slots[i];
        Rectangle iconeInv = { s.x, s.y, s.width, s.width };   
        DesenharIconeNoSlot(acessar(inventario, i).textura, iconeInv);
    }
 
    DrawText("INVENTARIO", (int)tela.painel.x, (int)tela.painel.y - 40, 30, WHITE);
    DrawText("[TAB] ou [I] para fechar", (int)tela.painel.x, (int)(tela.painel.y + tela.painel.height) + 14, 20, WHITE);

     if (tela.slotHover >= 0 && tamanho(inventario) > tela.slotHover) {
        DesenharDicaMouseInventario("Vence no Turno: ", inventario, tela.slotHover);
    }
}

void DesenharDicaMouseInventario(const char* texto,ListaContiguaINV &inventario, int escolhido) {
    const int tam = 18;
    int larg = MeasureText(texto, tam) + 10;

    Vector2 m = GetMousePosition();

    float x = m.x + 16;      
    float y = m.y + 20;

    if (x + larg + 16 > GetScreenWidth()) x = m.x - larg - 24;
    if (y + 28 > GetScreenHeight()) y = m.y - 36;

    if(acessar(inventario, escolhido).ehPerecivel){
        DrawRectangleRounded({ x, y, (float)larg + 16, 28 }, 0.4f, 6, Color{ 40, 28, 22, 230 });
        DrawText(texto, (int)x + 8, (int)y + 5, tam, WHITE);
        DrawText(TextFormat("%d", acessar(inventario, escolhido).turnoEstraga), (int)x + MeasureText("Turno que vence:", tam) + 8, (int)y + 5, tam, RED);
    }
}