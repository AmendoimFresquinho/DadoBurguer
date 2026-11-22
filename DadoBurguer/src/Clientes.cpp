#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include <string>
#include "Constantes.hpp"
#include <random>

Cliente criaClientePadrao(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, int &codigoMax, int &codigoMin, Log& relatorio){

    Cliente novo;

    novo.ehEspecial = false;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> Skin(1, 10);

    int SkinCliente = Skin(gen);

    switch (SkinCliente) {
    case 1:
        novo.sprite = sprites[0];
        break;
    case 2:
        novo.sprite = sprites[1];
        break;
    case 3:
        novo.sprite = sprites[2];
        break;
    case 4:
        novo.sprite = sprites[3];
        break;
    case 5:
        novo.sprite = sprites[4];
        break;
    case 6:
        novo.sprite = sprites[5];
        break;
    case 7:
        novo.sprite = sprites[6];
        break;
    case 8:
        novo.sprite = sprites[7];
        break;
    case 9:
        novo.sprite = sprites[8];
        break;
    case 10:
        novo.sprite = sprites[9];       
        break;

    default: break;
    }

    if(dificuldade == FACIL){
        std::uniform_int_distribution<> facil(8, 10);
        novo.Paciencia = facil(gen);
        novo.PacienciaPermante = novo.Paciencia;
    }
    if(dificuldade == MEDIO){
        std::uniform_int_distribution<> medio(6, 8);
        novo.Paciencia = medio(gen);
        novo.PacienciaPermante = novo.Paciencia;
    }
    if(dificuldade == DIFICIL){
        std::uniform_int_distribution<> dificil(4, 6);
        novo.Paciencia = dificil(gen);
        novo.PacienciaPermante = novo.Paciencia;
    }
    if(dificuldade == IMPOSSIVEL){
        std::uniform_int_distribution<> impossivel(2, 4);
        novo.Paciencia = impossivel(gen);
        novo.PacienciaPermante = novo.Paciencia;
    }

    novo.pedido = SorteiaPedidos(raiz, codigoMax, codigoMin, hash, HIT, MISS, relatorio);

    return novo;
}

Cliente CriaclienteEspecial(Texture2D sprites[2]){
    
    Cliente novo;

    novo.ehEspecial = true;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> qualEh(1, 2);

    int ESCOLHIDO = qualEh(gen);

    switch (ESCOLHIDO) {

    case 1:
        novo.sprite = sprites[0];
        novo.pedido = "xqsqsqsqsz";
        novo.Paciencia = 2;
        novo.PacienciaPermante = 2;
        break;
    case 2:
        novo.sprite = sprites[1];
        novo.pedido = "xkaqnxapnz"; //BIG MAC
        novo.PacienciaPermante = 5;
        break;
    default: break;
    }

    return novo;
}

void criaFilaClientes(Dificuldade &dificuldade, Texture2D sprites[10], NodoAvl *&raiz, TabelaEnc &hash, int &HIT, int &MISS, Texture2D Especiais[2], FilaEnc &Clientes, int &TAM_FILA, int &codigoMax, int &codigoMin, Log& relatorio){

    if(dificuldade == FACIL) TAM_FILA = TAMANHO_FILA_FACIL;
    else if(dificuldade == MEDIO) TAM_FILA = TAMANHO_FILA_MEDIO;
    else if(dificuldade == DIFICIL) TAM_FILA = TAMANHO_FILA_DIFICIL;
    else TAM_FILA = TAMANHO_FILA_IMPOSSIVEL;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> Especial(1, 20);

    int EhEspecial;

    for(int i = 0; i < TAM_FILA; i++){   

        EhEspecial = Especial(gen);

        if(EhEspecial >= 0 && EhEspecial <= 19){
            Cliente novo = criaClientePadrao(dificuldade, sprites, raiz, hash, HIT, MISS, codigoMax, codigoMin, relatorio);
            enfileira(Clientes, novo);
        }
        else {
            Cliente novo = CriaclienteEspecial(Especiais);
            enfileira(Clientes, novo);
        }
    }
}

void desenhaFila(FilaEnc &f){

    NodoFila *aux = f.frente;
    Vector2 Posicao = {680, 280};

    if(f.tamanho > 0){ // Anticrash
        for(int i = 0; i < 9; i++){   
            if(aux->dado.ehEspecial){
                SetTextureFilter(aux->dado.sprite, TEXTURE_FILTER_POINT);
                DrawTextureEx(aux->dado.sprite, Posicao, 0.0f, 1.0f, WHITE);
            }
            else{
                SetTextureFilter(aux->dado.sprite, TEXTURE_FILTER_POINT);
                DrawTextureEx(aux->dado.sprite, Posicao, 0.0f, 2.0f, WHITE);
            }
            if(aux->prox == nullptr)
                break;
            aux = aux->prox;
            Posicao.x += 60;
        }
    }
}

void desenhaPedido(FilaEnc &f, IngredienteJogo Ings[QUANTIDADE_INGREDIENTES], Texture2D &caixaPensamento){

    Rectangle origem = { 0, 0, (float)caixaPensamento.width, (float)caixaPensamento.height };
    Rectangle destinoEsp = { 700, 50, 96, 240 };
    Rectangle destinoNorm = { 700, 80, 96, 200 };

    if(f.tamanho > 0){
        SetTextureFilter(caixaPensamento, TEXTURE_FILTER_POINT);
        if (f.frente->dado.ehEspecial ) DrawTexturePro(caixaPensamento, origem, destinoEsp, {0,0}, 0.0f, WHITE);
        else DrawTexturePro(caixaPensamento, origem, destinoNorm, {0,0}, 0.0f, WHITE);

        for(int i = 0; i < f.frente->dado.pedido.size(); i++){
            char escolhido = f.frente->dado.pedido[i];
            Vector2 Posicao = {730, (float)(190 - (i * 14))};

            if(escolhido == 'z') DrawTextureEx(Ings[0].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'x') DrawTextureEx(Ings[1].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'u') DrawTextureEx(Ings[2].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'n') DrawTextureEx(Ings[13].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'l') DrawTextureEx(Ings[14].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 's') DrawTextureEx(Ings[17].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'q') DrawTextureEx(Ings[18].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'a') DrawTextureEx(Ings[5].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'k') DrawTextureEx(Ings[6].textura, {Posicao.x + 33, Posicao.y}, 90.0f, 1.0f, WHITE);
            if(escolhido == 'm') DrawTextureEx(Ings[7].textura, {Posicao.x + 33, Posicao.y}, 90.0f, 1.0f, WHITE);
            if(escolhido == 'p') DrawTextureEx(Ings[8].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'c') DrawTextureEx(Ings[20].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 't') DrawTextureEx(Ings[19].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'o') DrawTextureEx(Ings[15].textura, Posicao, 0.0f, 1.0f, WHITE);
            if(escolhido == 'b') DrawTextureEx(Ings[16].textura, Posicao, 0.0f, 1.0f, WHITE);
        }
    }
}

void checaSeAcertou(FilaEnc &f, int &pontuacao, Dificuldade &dificuldade, int &processos, TelaInventario &telaInv){

    int Multiplicador = 0, cont = 0;
    Image tmp_img = {0};

    if(dificuldade == FACIL) Multiplicador = PONTUACAO_ACERTO_FACIL;
    else if(dificuldade == MEDIO) Multiplicador = PONTUACAO_ACERTO_MEDIO;
    else if(dificuldade == DIFICIL) Multiplicador = PONTUACAO_ACERTO_DIFICIL;
    else Multiplicador = PONTUACAO_ACERTO_IMPOSSIVEL;

    if(f.frente->dado.pedido.size() - telaInv.hamburguer.quantDados > 0){
        pontuacao -= Multiplicador * (f.frente->dado.pedido.size() - telaInv.hamburguer.quantDados);
        cont++;
    }

    for(int i = telaInv.hamburguer.quantDados - 1; i >= 0; i--){
       
        if(telaInv.hamburguer.quantDados > f.frente->dado.pedido.size()){
            Montagem :: removerIngrediente(telaInv.hamburguer, tmp_img);
            pontuacao -= Multiplicador;
            std::cout << "MAIOR\n";
            std::cout << telaInv.hamburguer.quantDados << "\n";
            cont++;
            continue;
        }

        if (f.frente->dado.pedido[telaInv.hamburguer.quantDados - 1] == telaInv.hamburguer.topo->ingrediente){
            pontuacao += Multiplicador;
            std::cout << "CERTO\n";
            Montagem :: removerIngrediente(telaInv.hamburguer, tmp_img);
        }
        else{
            pontuacao -= Multiplicador;
            cont++;
            std::cout << "ERRADO\n";
            Montagem :: removerIngrediente(telaInv.hamburguer, tmp_img);
        }
    }

    if(cont) processos++;
    if(pontuacao < 0) pontuacao = 0;

    Cliente lixo;
    desenfileira(f, lixo);
    Montagem :: explodeHamburguer(telaInv.hamburguer);
    telaInv.temHamburgui = false;
}

void TelaConfirmacao(Texture2D &mainTela, Texture2D &sim, Texture2D &nao, EstadoJogo &estado, FilaEnc &f, int &pontuacao, Dificuldade &dificuldade, int &processos, TelaInventario &telaInv){

    Rectangle botaoSim = {404, 446, 211, 78};
    Rectangle botaoNao = {654, 446, 211, 78};

    DrawTexture(mainTela, 260, 146, WHITE);

    if(CheckCollisionPointRec(GetMousePosition(), botaoSim)){
        DrawTexture(sim, 404, 445, WHITE);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            checaSeAcertou(f, pontuacao, dificuldade, processos, telaInv);
            estado.tela = TELA_JOGO;
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), botaoNao)){
        DrawTexture(nao, 656, 445, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            estado.tela = TELA_JOGO;
    }
}
void desenhaBarraPaciencia( const FilaEnc& f, int pacienciaInicial, Texture2D verde, Texture2D vermelho, Texture2D vazio) {

    if (f.frente == nullptr || pacienciaInicial <= 0)
        return;

    int pacienciaAtual = f.frente->dado.Paciencia;

    const float lado = 12.0f;  // Antes era 8.
    const float espaco = 0.0f; // Quadrados encostados.
    const int porLinha = 5;

    int colunas = pacienciaInicial < porLinha ? pacienciaInicial : porLinha;

    float larguraLinha = colunas * lado + (colunas - 1) * espaco;
       
    float inicioX = 680.0f + (64.0f - larguraLinha) / 2.0f;

    SetTextureFilter(verde, TEXTURE_FILTER_POINT);
    SetTextureFilter(vermelho, TEXTURE_FILTER_POINT);
    SetTextureFilter(vazio, TEXTURE_FILTER_POINT);

    for (int i = 0; i < pacienciaInicial; i++) {
        int linha = i / porLinha;
        int coluna = i % porLinha;

        Texture2D textura = vazio;

        if (i < pacienciaAtual) {
            textura = pacienciaAtual <= 2 ? vermelho : verde;
        }

        Rectangle origem = { 0.0f, 0.0f, static_cast<float>(textura.width), static_cast<float>(textura.height)};

        Rectangle destino = { inicioX + 2 + coluna * (lado + espaco), 350.0f + linha * (lado + espaco), lado, lado };
       
        DrawTexturePro( textura, origem, destino, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
    }
}