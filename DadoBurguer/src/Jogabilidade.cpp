#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <cfloat>
#include <vector>
#include <string>
#include <iostream>
#include <random>

void passaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS){
    turno++;
    stamina = STAMINA; 
      if(HEAP_PERECIVEIS.tamanho > 0)
        verificaSeEstragou(HEAP_PERECIVEIS, Inventario, turno);
}

void BotaoPassaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS){

    Rectangle passaTurnoRec = {LARGURA - 157, ALTURA - 26.5, 150, 20 };
    DrawRectangleRounded(passaTurnoRec, 2.67, 67/6.7, LIGHTGRAY);
    DrawText("PASSAR TURNO", LARGURA - 151, ALTURA - 25, 18, RED);
     
    if(CheckCollisionPointRec(GetMousePosition(), passaTurnoRec)){
        DrawRectangleRounded(passaTurnoRec, 2.67, 67/6.7, Fade(WHITE, 0.4f));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            passaTurno(turno, stamina, Inventario, HEAP_PERECIVEIS);
    }
}

void desenhaTurno(const int &turno, const int &stamina){
    int distancia = 0;
    DrawText("Turno:", 5, 5, 20, BLACK);
    DrawText(TextFormat("%d", turno), MeasureText("Turno", 20) + 15, 5, 20, RED);
    DrawText("STAMINA:", 5, ALTURA - 25, 20, BLACK);
    for(int i = 0; i < stamina; i++){
        Rectangle STAM = {5.0f + distancia + MeasureText("STAMINA:", 22), ALTURA - 23, 30, 15};
        DrawRectangleRounded(STAM, 2, 4, LIGHTGRAY);
        distancia += 40;
    }
}

int gastaStamina(int &stamina, const int quantoGasta){
    return stamina = stamina - quantoGasta;
}

int testaStamina (const int &stamina, const int quantoGasta){
    return stamina - quantoGasta;
}

void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &menu, Texture2D &pausa, Texture2D &fundo, Texture2D &paoCima, Texture2D &paoBaixo,Texture2D &cheddar,Texture2D &suico, Texture2D &carne_crua, Texture2D &alface, Texture2D &tomate, Texture2D &ketchup, Texture2D &mostarda, Texture2D &cebola, Texture2D &ovo, Texture2D &bacon, Texture2D &picles){

    DescarregarAnimJogador(animJogador);
    DescarregarTelaEstoque(telaEstoque);
    UnloadTexture(menu);
    UnloadTexture(pausa);
    UnloadTexture(fundo);
    UnloadTexture(pausa);
    UnloadTexture(paoCima);
    UnloadTexture(paoBaixo);
    UnloadTexture(cheddar);
    UnloadTexture(suico);
    UnloadTexture(carne_crua);
    UnloadTexture(alface);
    UnloadTexture(tomate);
    UnloadTexture(ketchup);
    UnloadTexture(mostarda);
    UnloadTexture(cebola);
    UnloadTexture(ovo);
    UnloadTexture(bacon);
    UnloadTexture(picles);

    CloseWindow();
}

void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina, FilaPrioridade &heap) {
    jogador = { 250.0f, 64.0f, { 340, 360 }, { 0, 0 }, 32.0f, 64.0f };
    estado = { false, TELA_JOGO };
    anim.frame = 0;
    anim.tempo = 0.0f;
    anim.direcao = DIR_BAIXO;
    inv.tamanho = 0;
    stamina = STAMINA;
    turno = 0;
    heap.tamanho = 0;
}

void colocaNoHeapEstragado(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam, int &turno){

    if(Ingrediente->ehPerecivel){
        Ingrediente->turnoEstraga = turno + Ingrediente->turnoEstraga; 
        fpInserir(comidasEstragam, Ingrediente);
    }
}

void colocaNoHeapEstragadoSemTurno(IngredienteJogo *Ingrediente, FilaPrioridade &comidasEstragam){ //Para organizar sem ferrar com a validade

    if(Ingrediente->ehPerecivel){
        fpInserir(comidasEstragam, Ingrediente);
    }
}

void reconstroiHeapDesatualizado(ListaContiguaINV &inventario, FilaPrioridade &heap){ // serve como remocao do heap tambem, pq se remove do inventario e chama isso ele nao coloca o que foi removido do inventario

    heap.tamanho = 0; // zera o heap
    
    for(int i = 0; i < inventario.tamanho; i++){
        if(acessar(inventario, i).ehPerecivel){
            IngredienteJogo *p = enderecoDe(inventario, i);
            colocaNoHeapEstragadoSemTurno(p, heap);        
        }
    }
    buildHeap(heap.dados, heap.tamanho);
}

void verificaSeEstragou(FilaPrioridade &comidasEstragam, ListaContiguaINV &inventario, const int &turnoAtual){
    
    while(comidasEstragam.dados[0]->turnoEstraga <= turnoAtual && comidasEstragam.tamanho > 0){
        removeDoInventario(buscarIngrediente(inventario, comidasEstragam.dados[0]), inventario);
        reconstroiHeapDesatualizado(inventario, comidasEstragam);
    }
}
         
IngredienteJogo* enderecoDe(ListaContiguaINV &l, int pos){ // Uma versao de acessar que devolve ponteiro, pq senao da bo

    if (pos >= l.tamanho || pos < 0)
        return nullptr;

    return &l.dados[pos];
}

void fpImprimir(const FilaPrioridade &fp) { //FUNCAO TEMPORARIA PARA DEBUGAR

    std::cout << "Heap (tamanho " << fp.tamanho << ")\n";
    for (int i = 0; i < fp.tamanho; i++) {
        std::cout << "[" << i << "] " << fp.dados[i]->codigo << "  turnoEstraga=" << fp.dados[i]->turnoEstraga;

        // a raiz é o menor, então nenhum filho pode ser menor que o pai
        if (i > 0 && fp.dados[i]->turnoEstraga < fp.dados[(i - 1) / 2]->turnoEstraga)
            std::cout << "  <-- viola o heap";

        std::cout << "\n";
    }
}