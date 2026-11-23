#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include <vector>
#include "Constantes.hpp"

void iniciaTelaMesaCorte(TelaMesaCorte &t, const Texture2D &texFaca) {
    float L = (float)GetScreenWidth();
    float A = (float)GetScreenHeight();

    t.moldura = { L * 0.05f, A * 0.08f, L * 0.90f, A * 0.84f };
    const Rectangle &m = t.moldura;

    // proporções tiradas do seu desenho
    t.tabua = { m.x + m.width * 0.020f, m.y + m.height * 0.038f, m.width * 0.326f, m.height * 0.923f };
    t.painelFaca = { m.x + m.width * 0.356f, m.y + m.height * 0.042f, m.width * 0.158f, m.height * 0.924f };
    t.gradeInv = { m.x + m.width * 0.539f, m.y + m.height * 0.038f, m.width * 0.448f, m.height * 0.936f };

    // 9 slots em grade 3x3
    t.slotsInv.clear();
    float cw = t.gradeInv.width  / 3.0f;
    float ch = t.gradeInv.height / 3.0f;
    for (int i = 0; i < 9; i++)
        t.slotsInv.push_back({ t.gradeInv.x + (i % 3) * cw, t.gradeInv.y + (i / 3) * ch, cw, ch });

    // faca centralizada no painel, com escala calculada para caber
    t.escalaFaca = fminf(t.painelFaca.width  * 0.70f / texFaca.width, t.painelFaca.height * 0.88f / texFaca.height);
    float fw = texFaca.width  * t.escalaFaca;
    float fh = texFaca.height * t.escalaFaca;
    t.facaRepouso = { t.painelFaca.x + (t.painelFaca.width - fw) / 2.0f, t.painelFaca.y + (t.painelFaca.height - fh) / 2.0f }; 
    t.faca = { t.facaRepouso.x, t.facaRepouso.y, fw, fh };
}

bool AtualizarTelaCorte(TelaMesaCorte& tela) {
    Vector2 mouse = GetMousePosition();
 
    tela.slotHover = -1;
    for (size_t i = 0; i < tela.slotsInv.size(); i++) {
        if (CheckCollisionPointRec(mouse, tela.slotsInv[i])) tela.slotHover = (int)i;
    }

    tela.escolhidoINV = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? tela.slotHover : -1;

    tela.tabuaHover = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ? tela.tabuaHover : -1;

    return IsKeyPressed(KEY_E);
}

void desenhaTelaMesaCorte(TelaMesaCorte &t, ListaContiguaINV &inventario, const Texture2D &texFaca, const Texture2D &texCebolaFeita, const Texture2D &texTomateFeito, int &stamina, FilaPrioridade &HEAP, SFX_PACK& sfx) {
    // moldura e painéis
    DrawRectangleRec(t.moldura, WHITE);
    DrawRectangleLinesEx(t.moldura, 4, BLACK);
    DrawRectangleLinesEx(t.tabua, 3, BLACK);
    DrawRectangleLinesEx(t.painelFaca, 3, BLACK);
    DrawRectangleLinesEx(t.gradeInv, 4, BLACK);

    Vector2 mouse = GetMousePosition();
    Vector2 centroTabua = { t.tabua.x + t.tabua.width  / 2.0f, t.tabua.y + t.tabua.height / 2.0f };
    float yLinha = t.tabua.y + t.tabua.height * 0.04f + 10;
    Vector2 centroUtil = { t.tabua.x + t.tabua.width / 2.0f, (yLinha + t.tabua.y + t.tabua.height) / 2.0f };
    float escala = 6.0f;
    Rectangle Centro = { t.tabua.x + (t.tabua.width - 192) / 2.0f, t.tabua.y + (t.tabua.height - 192) / 2.0f, 192, 192 };

    // inventário 3x3
    for (int i = 0; i < 9; i++) {
        
        if (i == t.slotHover)
            DrawRectangleRec(t.slotsInv[i], { 255, 200, 0, 40 });
           
        DrawRectangleLinesEx(t.slotsInv[i], 2, BLACK);
    }

    int hover = t.slotHover;

    IngredienteJogo *ing = enderecoDe(inventario, hover);
    if (ing != nullptr && (ing->codigo == 'T' || ing->codigo == 'C') && !t.temNaTabua && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        IngredienteJogo p = *ing;
        t.itemTabua = p;
        t.temNaTabua = true;
        imprime(inventario);
        removeDoInventario(hover, inventario);
        reconstroiHeapDesatualizado(inventario, HEAP);
        imprime(inventario);
    }

    if(t.temNaTabua && CheckCollisionPointRec(mouse, Centro) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && inventario.tamanho < 9){
        inserir(inventario, t.itemTabua, inventario.tamanho);
        t.itemTabua = {};
        t.temNaTabua = false;
        reconstroiHeapDesatualizado(inventario, HEAP);
    }

    for(int i = 0; i < inventario.tamanho; i++)
        DesenharIconeNoSlot(acessar(inventario, i).textura, t.slotsInv[i]);

    if(t.temNaTabua){
        Vector2 pos = { centroUtil.x - t.itemTabua.textura.width  * escala / 2.0f, centroUtil.y - t.itemTabua.textura.height * escala / 2.0f };
        DrawTextureEx(t.itemTabua.textura, pos, 0.0f, escala, WHITE);
    }

    // faca 
    Vector2 pos2 = t.facaPegada ? Vector2{ GetMousePosition().x - t.offsetPegada.x, GetMousePosition().y - t.offsetPegada.y } : t.facaRepouso;
    
    if(CheckCollisionPointRec(mouse, t.faca) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !t.facaPegada){
        t.facaPegada = true;
        pegaFaca(t);  
    }

    if(CheckCollisionPointRec(mouse, t.faca) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && t.facaPegada){
        t.facaPegada = false;
    }

    if(t.facaPegada){
        Vector2 p = { mouse.x - t.offsetPegada.x, mouse.y - t.offsetPegada.y };
        Rectangle aux = { p.x + LAMINA_X * t.escalaFaca, p.y + LAMINA_Y * t.escalaFaca, LAMINA_W * t.escalaFaca, LAMINA_H * t.escalaFaca }; 
        
        if(CheckCollisionRecs(aux, Centro) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && (t.itemTabua.codigo == 'T' || t.itemTabua.codigo == 'C')){
            
            stamina--;
            
            PlaySound(sfx.corte);

            if(t.itemTabua.codigo == 'T'){
                t.itemTabua = {'t', false, texTomateFeito, "Tomate Feito", 0};
            }
            if(t.itemTabua.codigo == 'C'){
                t.itemTabua = {'c', false, texCebolaFeita, "Cebola Feita", 0};
            }
        }
    }

    DrawTextureEx(texFaca, pos2, 0.0f, t.escalaFaca, WHITE);
    
}

void pegaFaca(TelaMesaCorte &t) {
    t.offsetPegada = { (CABO_X + CABO_W / 2) * t.escalaFaca, (CABO_Y + CABO_H / 2) * t.escalaFaca }; 
}