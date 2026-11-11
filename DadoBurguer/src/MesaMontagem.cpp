#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include <vector>
#include "Constantes.hpp"
#include "Ingredientes.hpp"

void iniciaTelaMontagem(TelaMontagem &t) {
    float L = (float)GetScreenWidth();
    float A = (float)GetScreenHeight();

    t.moldura = { L * 0.05f, A * 0.08f, L * 0.90f, A * 0.84f };
    const Rectangle &m = t.moldura;

    t.painelHamb = { m.x + m.width * 0.0075f, m.y + m.height * 0.051f, m.width * 0.485f, m.height * 0.918f };
    t.painelInv  = { m.x + m.width * 0.506f,  m.y + m.height * 0.051f, m.width * 0.485f, m.height * 0.918f };

    t.slotsInv.clear();
    float cw = t.painelInv.width  / 3.0f;
    float ch = t.painelInv.height / 3.0f;
    for (int i = 0; i < 9; i++)
        t.slotsInv.push_back({ t.painelInv.x + (i % 3) * cw, t.painelInv.y + (i / 3) * ch, cw, ch });
    for(int i = 0; i < 10; i++)
        t.IngsNoHamburger[i] = {};
}

bool AtualizarTelaMontagem(TelaMontagem& tela) {
    Vector2 mouse = GetMousePosition();
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slotsInv.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slotsInv[i])) tela.slotHover = (int)i;
    }
 
    tela.escolhidoINV = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? tela.slotHover : -1;
 
    return IsKeyPressed(KEY_E);
}

void desenhaTelaMontagem(TelaMontagem &t, ListaContiguaINV &inventario, Image &tmp_img, FilaPrioridade &HEAP, const int &Turno) {
    DrawRectangleRec(t.moldura, WHITE);
    DrawRectangleLinesEx(t.moldura, 4, BLACK);
    DrawRectangleLinesEx(t.painelHamb, 4, BLACK);
    DrawRectangleLinesEx(t.painelInv, 4, BLACK);

    Vector2 mouse = GetMousePosition();
    DrawTextureEx(t.hamburguer.textura, baseHamburguer(t.painelHamb), 0.0f, escalaHamburguer(t.painelHamb), WHITE);
    Rectangle CentroHamburguer = { 249, 294, 218, 166 };

    // inventário 3x3
    for (int i = 0; i < 9; i++) {
        if (i == t.slotHover)
            DrawRectangleRec(t.slotsInv[i], LIGHTGRAY);
        DrawRectangleLinesEx(t.slotsInv[i], 2, BLACK);
    }

    IngredienteJogo *ing = enderecoDe(inventario, t.slotHover);
  
    if (ing != nullptr && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(ing->codigo >= 65 && ing->codigo <= 90) && t.hamburguer.altura <= 10) {

        t.IngsNoHamburger[t.hamburguer.quantDados] = *ing;

        if(ing->codigo == 'a') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::ALFACE, tmp_img);
        if(ing->codigo == 'n') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::CARNE, tmp_img);
        if(ing->codigo == 'u') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::CARNE_ASSADA, tmp_img);
        if(ing->codigo == 't') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::TOMATE, tmp_img);
        if(ing->codigo == 'q') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::CHEDDAR, tmp_img);
        if(ing->codigo == 'x') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::PAO_BAIXO, tmp_img);
        if(ing->codigo == 's') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::SUICO, tmp_img);
        if(ing->codigo == 'k') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::KETCHUP, tmp_img);
        if(ing->codigo == 'm') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::MOSTARDA, tmp_img);
        if(ing->codigo == 'p') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::PICLES, tmp_img);
        if(ing->codigo == 'c') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::CEBOLA, tmp_img);
        if(ing->codigo == 'o') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::OVO, tmp_img);
        if(ing->codigo == 'l') Montagem::adicionarIngrediente(t.hamburguer, Ingredientes::CARNE_QUEIMADA, tmp_img);
        removeDoInventario(t.slotHover, inventario);
        reconstroiHeapDesatualizado(inventario, HEAP);
        imprimirPilha(t.hamburguer);    
    }

    if(CheckCollisionPointRec(mouse, CentroHamburguer) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && t.hamburguer.quantDados > 0){
        Montagem::removerIngrediente(t.hamburguer, tmp_img);
        if(t.IngsNoHamburger[t.hamburguer.quantDados].ehPerecivel)
            t.IngsNoHamburger[t.hamburguer.quantDados].turnoEstraga = Turno + 2;
        inserir(inventario,t.IngsNoHamburger[t.hamburguer.quantDados], inventario.tamanho);
        reconstroiHeapDesatualizado(inventario, HEAP);
    } 
     
    for(int i = 0; i < inventario.tamanho; i++)
        DesenharIconeNoSlot(acessar(inventario, i).textura, t.slotsInv[i]);

}

float escalaHamburguer(const Rectangle &painel) {
    constexpr float LARGURA_HAMB_TEX  = 54;   
    constexpr float ALTURA_CAMADA_TEX = 13; 
    float porLargura = painel.width  * 0.60f / LARGURA_HAMB_TEX;
    float porAltura  = painel.height * 0.80f / (ALTURA_CAMADA_TEX * 7);
    return fmaxf(1.0f, floorf(fminf(porLargura, porAltura)));   
}

// onde a base do hambúrguer deve ficar: centro do painel, perto do fundo
Vector2 baseHamburguer(const Rectangle &painel) {
    return { painel.x + painel.width / 3.5f, painel.y + painel.height * 0.35f };
}

void imprimirPilha(const Montagem::Pilha& pilha) {
    Montagem::Nodo* atual = pilha.topo;

    while (atual != nullptr) {
        std::cout << static_cast<char>(atual->ingrediente) << " ";
        atual = atual->prox;
    }

    std::cout << std::endl;
}