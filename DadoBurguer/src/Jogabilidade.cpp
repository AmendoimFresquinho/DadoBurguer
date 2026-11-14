#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include "Montagem.hpp"
#include <iostream>

void passaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS, Dificuldade &dificuldade){
    turno++;
    stamina = configuraDificuldadeStamina(dificuldade, stamina); 
      if(HEAP_PERECIVEIS.tamanho > 0)
        verificaSeEstragou(HEAP_PERECIVEIS, Inventario, turno);
}

void BotaoPassaTurno(int &turno, int &stamina, ListaContiguaINV &Inventario, FilaPrioridade &HEAP_PERECIVEIS, Dificuldade &dificuldade){

    Rectangle passaTurnoRec = {LARGURA - 157, ALTURA - 26.5, 150, 20 };
    DrawRectangleRounded(passaTurnoRec, 2.67, 67/6.7, LIGHTGRAY);
    DrawText("PASSAR TURNO", LARGURA - 151, ALTURA - 25, 18, RED);
     
    if(CheckCollisionPointRec(GetMousePosition(), passaTurnoRec)){
        DrawRectangleRounded(passaTurnoRec, 2.67, 67/6.7, Fade(WHITE, 0.4f));
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            passaTurno(turno, stamina, Inventario, HEAP_PERECIVEIS, dificuldade);
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

void desenhaPontuacao(const int &pontuacao){

}

void desenhaProcessos(const int &processos){
    int distancia = 0;
    DrawText("PROCESSOS:", 400, ALTURA - 25, 20, BLACK);
    for(int i = 0; i < processos; i++){
        Rectangle PROC = {400.0f + distancia + MeasureText("PROCESSOS:", 22), ALTURA - 23, 30, 15};
        DrawRectangleRounded(PROC, 2, 4, RED);
        distancia += 40;
    }
}

int gastaStamina(int &stamina, const int quantoGasta){
    return stamina = stamina - quantoGasta;
}

int testaStamina (const int &stamina, const int quantoGasta){
    return stamina - quantoGasta;
}

void FechaJogo(AnimJogador &animJogador, TelaEstoque &telaEstoque, Texture2D &hambuergao, Texture2D &RENDER, Image &IMAGEMHAMBURGUER, Texture2D texturas[50]){

    DescarregarAnimJogador(animJogador);
    DescarregarTelaEstoque(telaEstoque);
    for(int i = 0; i < 49; i++){
        UnloadTexture(texturas[i]);
    }
    UnloadTexture(RENDER);
    UnloadTexture(hambuergao);
    UnloadImage(IMAGEMHAMBURGUER);

    CloseWindow();
}

void ReiniciarJogo(Jogador& jogador, EstadoJogo& estado, AnimJogador& anim, ListaContiguaINV &inv, int &turno, int &stamina, FilaPrioridade &heap, TabelaEnc &hash, TelaFogao &telafogao, TelaMesaCorte &telaCorte, TelaInventario &telaInv, TelaMontagem &telaMonta, Dificuldade &dificuldade, FilaEnc &fila, int &processos, int &pontuacao){
    jogador = { 250.0f, 64.0f, { 340, 360 }, { 0, 0 }, 32.0f, 64.0f };
    estado = { false, TELA_JOGO };
    anim.frame = 0;
    anim.tempo = 0.0f;
    anim.direcao = DIR_BAIXO;
    inv.tamanho = 0;
    stamina = configuraDificuldadeStamina(dificuldade, stamina);
    turno = 0;
    heap.tamanho = 0;
    encDestruir(hash);
    telafogao.carnes.tamanho = 0;
    telaCorte.temNaTabua = false;
    telaCorte.itemTabua = {};
    telaInv.temHamburgui = false;
    telaInv.hamburguer = {}; 
    Montagem :: explodeHamburguer(telaMonta.hamburguer);
    for(int i = 0; i < 10; i++)
        telaMonta.IngsNoHamburger[i] = {};
    telaMonta.temNaTabua = false;
    liberaFila(fila);
    processos = 0;
    pontuacao = 0;
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