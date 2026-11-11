#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include <vector>
#include "Constantes.hpp"

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

void desenhaTelaMontagem(const TelaMontagem &t, ListaContiguaINV &inventario) {
    DrawRectangleRec(t.moldura, WHITE);
    DrawRectangleLinesEx(t.moldura, 4, BLACK);
    DrawRectangleLinesEx(t.painelHamb, 3, BLACK);
    DrawRectangleLinesEx(t.painelInv, 3, BLACK);

    // hambúrguer no centro do painel da esquerda
    Vector2 centroHamb = { t.painelHamb.x + t.painelHamb.width  / 2.0f, t.painelHamb.y + t.painelHamb.height / 2.0f };
    // SEU: desenhe t.hamburguer centrado em centroHamb (a sua dupla já faz o desenho)

    // inventário 3x3
    for (int i = 0; i < 9; i++) {
        if (i == t.slotHover)
            DrawRectangleRec(t.slotsInv[i], LIGHTGRAY);
        DrawRectangleLinesEx(t.slotsInv[i], 2, BLACK);

        IngredienteJogo *ing = enderecoDe(inventario, i);
        if (ing != nullptr) {
            // SEU: desenhe o ingrediente em t.slotsInv[i] (mesma função das outras telas)
        }
    }
}
    