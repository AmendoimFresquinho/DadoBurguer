#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "raymath.h"
#include "Constantes.hpp"
#include <vector>
#include <string>
#include <iostream>
#include "Montagem.hpp"

int main() {
    
    InitWindow((int)LARGURA, (int)ALTURA, "DADOBURGUER");
    SetTargetFPS(60);

    Texture2D paoCima = LoadTexture("DadoBurguer/assets/INV/cima_pao_inventario.png");
    Texture2D paoBaixo = LoadTexture("DadoBurguer/assets/INV/baixo_pao_inventario.png");
    Texture2D cheddar = LoadTexture("DadoBurguer/assets/INV/cheddar_cru.png");
    Texture2D suico = LoadTexture("DadoBurguer/assets/INV/suico_cru.png");
    Texture2D carne_crua = LoadTexture("DadoBurguer/assets/INV/carne_crua_inventario.png");
    Texture2D alface = LoadTexture("DadoBurguer/assets/INV/alface.png");
    Texture2D tomate = LoadTexture("DadoBurguer/assets/INV/tomate_cru.png");    
    Texture2D ketchup = LoadTexture("DadoBurguer/assets/INV/ketchup.png");
    Texture2D mostarda = LoadTexture("DadoBurguer/assets/INV/mostarda.png");
    Texture2D cebola = LoadTexture("DadoBurguer/assets/INV/cebola_crua.png");
    Texture2D ovo = LoadTexture("DadoBurguer/assets/INV/ovo_cru.png");
    Texture2D bacon = LoadTexture("DadoBurguer/assets/INV/bacon_cru.png");
    Texture2D picles = LoadTexture("DadoBurguer/assets/INV/picles.png");
    Texture2D carne_assada = LoadTexture("DadoBurguer/assets/INV/carne_assada_inventario.png");
    Texture2D mouse = LoadTexture("DadoBurguer/assets/mouse.png");
    Texture2D panela = LoadTexture("DadoBurguer/assets/panela.png");
    Texture2D fogo = LoadTexture("DadoBurguer/assets/fogo.png");
    Texture2D carne_queimada = LoadTexture("DadoBurguer/assets/INV/carne_queimada_inventario.png");
    Texture2D ovoFrito = LoadTexture("DadoBurguer/assets/INV/ovo.png");
    Texture2D baconFrito = LoadTexture("DadoBurguer/assets/INV/bacon_cozido.png");
    Texture2D suicoFrito = LoadTexture("DadoBurguer/assets/INV/suico_frito.png");
    Texture2D cheddarFrito = LoadTexture("DadoBurguer/assets/INV/cheddar_frito.png");
    Texture2D cebolaFeita = LoadTexture("DadoBurguer/assets/INV/cebola.png");
    Texture2D tomateFeito = LoadTexture("DadoBurguer/assets/INV/tomate.png");    

    Rectangle mouseRect = {0.0f, 0.0f, (float) mouse.width, (float) mouse.height};
    float mouseLarg, mouseEscala;
    Rectangle mouseDestRect;

    IngredienteJogo Pao_cima = { 'z', false, paoCima, "Pao de Cima", 0 };
    IngredienteJogo Pao_baixo ={ 'x', false, paoBaixo, "Pao de Baixo", 0 };
    IngredienteJogo Carne = { 'n', true, carne_crua, "Carne", VALIDADE_CARNE_CRUA };
    IngredienteJogo Queijo_Suico = { 'S', false, suico, "Suico", 0 };
    IngredienteJogo Cheddar = { 'Q', false, cheddar, "Cheddar", 0 };
    IngredienteJogo Alface = { 'a', false, alface, "Alface", 0};
    IngredienteJogo Ketchup = { 'k', false, ketchup, "Ketchup", 0};
    IngredienteJogo Mostarda = { 'm', false, mostarda, "Mostarda", 0};
    IngredienteJogo Picles = { 'p', false, picles, "Picles", 0};
    IngredienteJogo Cebola = { 'C', false, cebola, "Cebola Crua", 0};
    IngredienteJogo Tomate = { 'T', false, tomate, "Tomate Cru", 0};    
    IngredienteJogo Ovo = { 'O', true, ovo, "Ovo", VALIDADE_QUEIJO};
    IngredienteJogo Bacon = { 'B', true, bacon, "Bacon", VALIDADE_QUEIJO};
    IngredienteJogo Carne_Assada = {'u', true, carne_assada, "Carne Assada", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Carne_Queimada = {'l', true, carne_queimada, "Carne Queimada", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Ovo_Frito = {'o', true, ovoFrito, "Ovo Frito", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Bacon_Frito = {'b', true, baconFrito, "Bacon Frito", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Suico_Frito = {'s', true, suicoFrito, "Suico Feito", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Cheddar_Frito = {'q', true, cheddarFrito, "Cheddar Feito", VALIDADE_CARNE_ASSADA};
    IngredienteJogo Cebola_Feita = { 'c', false, cebolaFeita, "Cebola", 0};
    IngredienteJogo Tomate_Feito = { 't', false, tomateFeito, "Tomate", 0};    

    IngredienteJogo Ingredientes_Para_Passar[QUANTIDADE_INGREDIENTES] = {Pao_cima, Pao_baixo, Carne, Queijo_Suico, Cheddar, Alface, Ketchup, Mostarda, Picles, Cebola, Tomate, Ovo, Bacon, Carne_Assada, Carne_Queimada, Ovo_Frito, Bacon_Frito, Suico_Frito, Cheddar_Frito, Tomate_Feito, Cebola_Feita};

    Texture2D menu = LoadTexture("DadoBurguer/assets/Menu.png");
    Texture2D pausa = LoadTexture("DadoBurguer/assets/pausa.png");
    Texture2D fundo = LoadTexture("DadoBurguer/assets/fundo.png");
    Texture2D texFaca = LoadTexture("DadoBurguer/assets/faca.png");

    ESTADO_PROGRAMA EstadoPrograma = MENU; 
    std::vector<Rectangle> paredes;
    std::vector<Bloco> blocos;
    
    ConstruirMapa(paredes, blocos);
    AnimJogador animJogador = CriarAnimJogador("DadoBurguer/assets/jogador.png");
    TelaFogao telaFogao = CriarTelaFogao(LARGURA, ALTURA);
    TelaEstoque telaEstoque = CriarTelaEstoque(LARGURA, ALTURA, Ingredientes_Para_Passar);
    TelaInventario telaInventario = CriarTelaInventario(LARGURA, ALTURA);
    TelaMesaCorte telaCorte;
    iniciaTelaMesaCorte(telaCorte, texFaca);             
    EstadoJogo estado = { false, TELA_JOGO };
    std::vector<Rectangle> solidos = paredes;
    
    FilaPrioridade HEAP_PERECIVEIS;
    HEAP_PERECIVEIS.tamanho = 0;

    ListaContiguaINV Inventario;
    Inventario.tamanho = 0;
    int Turno = 0;
    int Stamina = STAMINA;

    TabelaEnc HashPedidos;
    encInicializar(HashPedidos, TAMANHO_HASH);

    for (size_t i = 0; i < blocos.size(); i++) 
        solidos.push_back(blocos[i].rect);

    Jogador jogador = { 250.0f, 64.0f, { 350, 360 }, { 0, 0 }, 32.0f, 64.0f };

    Rectangle btnIniciar = { POS_X, POS_Y_INICIAL + (0 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO }; // Menu
    Rectangle btnDificuldade = { POS_X, POS_Y_INICIAL + (1 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnComoJogar = { POS_X, POS_Y_INICIAL + (2 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnHistorico = { POS_X, POS_Y_INICIAL + (3 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };
    Rectangle btnSair = { POS_X, POS_Y_INICIAL + (4 * ESPACAMENTO), LARGURA_BOTAO, ALTURA_BOTAO };

    Rectangle pausaVoltar = { 480, 268, 320, 76 }; // Pausa
    Rectangle pausaReiniciar = { 480, 366, 320, 76 };
    Rectangle pausaMenu = { 480, 464, 320, 76 };

    NodoAvl *Raiz = nullptr;
    int CodigoMax = 0, CodigoMin = INT_MAX, HIT = 0, MISS = 0;

    int TurnoAssado[4] = {};
    int QualTurno = 0;

    std :: vector<Historico> historico;
    historico.clear();
    carregaHistorico("DadoBurguer/Arquivos/historico.txt", historico);
    mergeSort(historico);
    std :: string nome;
    nome.clear();
    int pontuacao = Turno;
    imprimeHistorico(historico, 10);

    carregaPedidos("DadoBurguer/Arquivos/pedidos.txt", Raiz, CodigoMax, CodigoMin);
    std :: cout << "\n" << SorteiaPedidos(Raiz, CodigoMax, CodigoMin, HashPedidos, HIT, MISS)<< "\n";
    std :: cout << SorteiaPedidos(Raiz, CodigoMax, CodigoMin, HashPedidos, HIT, MISS)<< "\n";
    std :: cout << SorteiaPedidos(Raiz, CodigoMax, CodigoMin, HashPedidos, HIT, MISS)<< "\n";
    std :: cout << SorteiaPedidos(Raiz, CodigoMax, CodigoMin, HashPedidos, HIT, MISS)<< "\n";
    std :: cout << SorteiaPedidos(Raiz, CodigoMax, CodigoMin, HashPedidos, HIT, MISS)<< "\n";
    std :: cout << "\n ACERTOS: " << HIT << "\n ERROS: " << MISS << "\n";
    encImprimir(HashPedidos);

    Montagem::Pilha hamburguer = Montagem::Pilha();
    hamburguer.image = GenImageColor(64, 256, BLANK);
    hamburguer.textura = LoadTextureFromImage(hamburguer.image);
    Image tmp_img = {0};
    bool renderTeste = false;
    Texture2D telaRenderTeste = LoadTexture("DadoBurguer/assets/teclasRenderTeste.png");
    TelaMontagem telaMontagem;
    telaMontagem.hamburguer = hamburguer;
    iniciaTelaMontagem(telaMontagem);                 
    /*Montagem::carregarImagem(Ingredientes::CARNE, Mont_Carne);
    Texture2D txt = LoadTextureFromImage(Mont_Carne);
    UnloadImage(Mont_Carne);
    Mont_Carne = LoadImage("DadoBurguer/assets/Montagem/BifeCinza.png");
    Texture2D txt2 = LoadTextureFromImage(Mont_Carne);
    UnloadImage(Mont_Carne);*/

    while (!WindowShouldClose()) {
        HideCursor();
        Bloco* alvo = ProcuraInteragir(jogador, blocos, REACH); // Sempre procura um bloco possivelmente interagivel
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();

        //DrawTexture(txt, 50, 50, WHITE);

        float dt = GetFrameTime();

        switch(EstadoPrograma){

            case JOGANDO: { //Caso o jogador esteja jogando

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                //HideCursor();

                if(IsKeyPressed(KEY_J)) EstadoPrograma = FIM_JOGO;

                if(IsKeyPressed(KEY_ESCAPE)) 
                    EstadoPrograma = PAUSADO;
                if(Stamina <= 0)
                    passaTurno(Turno, Stamina, Inventario, HEAP_PERECIVEIS);
                
                pontuacao = Turno;

                Vector2 antes = jogador.posicao;

                switch (estado.tela) { // SWITCH CASE DE LOGICA
                
                    case TELA_JOGO:
                        Movimentacao(jogador);
                        Colisoes(jogador, dt, solidos);
                        AtualizarAnimJogador(animJogador, Vector2Subtract(jogador.posicao, antes), dt);
                        if (alvo != nullptr && IsKeyPressed(KEY_E) && testaStamina(Stamina, alvo->staminaGasta) >= 0){
                            FazInteracao(*alvo, estado);
                            gastaStamina(Stamina, alvo->staminaGasta);
                        } 
                        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_I)) estado.tela = TELA_INVENTARIO;
                        break;

                    case TELA_FOGAO: {

                        int escolhidoFogBoc = -1;
                        int escolhidoFogInv = -1;
                        if (AtualizarTelaFogao(telaFogao, escolhidoFogInv, escolhidoFogBoc, Inventario)) 
                            estado.tela = TELA_JOGO;
                            
                        //std :: cout << "\n TAMANHO CARNES: "<< telaFogao.carnes.tamanho<< "\n";
                        //std :: cout << "\n TAMANHO INVENTARIO: "<< Inventario.tamanho << "\n";

                        if(escolhidoFogInv != -1 && telaFogao.carnes.tamanho < 4 && (acessar(Inventario, escolhidoFogInv).codigo == 'n' || acessar(Inventario, escolhidoFogInv).codigo == 'O' || acessar(Inventario, escolhidoFogInv).codigo == 'B' || acessar(Inventario, escolhidoFogInv).codigo == 'Q' || acessar(Inventario, escolhidoFogInv).codigo == 'S')){
                        
                            TurnoAssado[QualTurno] = Turno;
                            QualTurno++;

                            std :: cout << "\n Turno que deve assar (INV): " << TurnoAssado[QualTurno - 1] << "\n";
                            std :: cout << "\n posicao do vetor (INV): "<< QualTurno << "\n";

                            if(acessar(Inventario, escolhidoFogInv).codigo == 'n'){
                                inserir(telaFogao.carnes, Carne, telaFogao.carnes.tamanho);
                                imprime(telaFogao.carnes);
                                removeDoInventario(escolhidoFogInv, Inventario);
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            }
                            else if(acessar(Inventario, escolhidoFogInv).codigo == 'O'){
                                inserir(telaFogao.carnes, Ovo, telaFogao.carnes.tamanho);
                                imprime(telaFogao.carnes);
                                removeDoInventario(escolhidoFogInv, Inventario);
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            }
                            else if(acessar(Inventario, escolhidoFogInv).codigo == 'B'){
                                inserir(telaFogao.carnes, Bacon, telaFogao.carnes.tamanho);
                                imprime(telaFogao.carnes);
                                removeDoInventario(escolhidoFogInv, Inventario);
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            }  
                            else if(acessar(Inventario, escolhidoFogInv).codigo == 'S'){
                                inserir(telaFogao.carnes, Queijo_Suico, telaFogao.carnes.tamanho);
                                imprime(telaFogao.carnes);
                                removeDoInventario(escolhidoFogInv, Inventario);
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            }
                            else if(acessar(Inventario, escolhidoFogInv).codigo == 'Q'){
                                inserir(telaFogao.carnes, Cheddar, telaFogao.carnes.tamanho);
                                imprime(telaFogao.carnes);
                                removeDoInventario(escolhidoFogInv, Inventario);
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            }
                        }
                        
                        if(escolhidoFogBoc != -1 && enderecoDe(telaFogao.carnes, escolhidoFogBoc) != nullptr && acessar(telaFogao.carnes, escolhidoFogBoc).codigo != 'n' && acessar(telaFogao.carnes, escolhidoFogBoc).codigo != 'O' && acessar(telaFogao.carnes, escolhidoFogBoc).codigo != 'B' && acessar(telaFogao.carnes, escolhidoFogBoc).codigo != 'S' && acessar(telaFogao.carnes, escolhidoFogBoc).codigo != 'Q'){
                            
                            TurnoAssado[escolhidoFogBoc] = 0;
                            for (int i = escolhidoFogBoc; i < QualTurno - 1; i++)
                                TurnoAssado[i] = TurnoAssado[i + 1];
                            QualTurno--;

                            std :: cout << "\n Turno que deve assar (BOC): " << TurnoAssado[QualTurno - 1] << "\n";
                            std :: cout << "\n posicao do vetor (BOC): "<< QualTurno << "\n";

                            if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 'u'){
                                IngredienteJogo Carne_atualizada = {'u', true, carne_assada, "Carne Assada", Turno + 1};
                                inserir(Inventario, Carne_atualizada, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }
                            else if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 'l'){
                                IngredienteJogo Carne_atualizada2 = {'l', true, carne_queimada, "Carne Queimada", Turno + 1};
                                inserir(Inventario, Carne_atualizada2, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }
                            else if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 'b'){
                                IngredienteJogo Bacon_Atualizado = {'b', true, baconFrito, "Bacon Frito", Turno + 1};
                                inserir(Inventario, Bacon_Atualizado, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }
                            else if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 'o'){
                                IngredienteJogo Ovo_Atualizado = {'o', true, ovoFrito, "Ovo Frito", Turno + 1};
                                inserir(Inventario, Ovo_Atualizado, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }
                            else if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 'q'){
                                IngredienteJogo Cheddar_Atualizado = {'q', true, cheddarFrito, "Cheddar Feito", Turno + 1};
                                inserir(Inventario, Cheddar_Atualizado, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }  
                            else if(acessar(telaFogao.carnes, escolhidoFogBoc).codigo == 's'){
                                IngredienteJogo Suico_Atualizado = {'s', true, suicoFrito, "Suico Feito", Turno + 1};
                                inserir(Inventario, Suico_Atualizado, Inventario.tamanho); 
                                reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                                remover(telaFogao.carnes, escolhidoFogBoc);
                            }
                            imprime(telaFogao.carnes);
                        }
                        break;
                    }
                    case TELA_ESTOQUE:
                        char escolhidoEST;
                        int escolhidoINV;
                        if (AtualizarTelaEstoque(telaEstoque, escolhidoEST, escolhidoINV)) estado.tela = TELA_JOGO;
                        if(escolhidoEST != '\0' && Inventario.tamanho < CAPACIDADE) {
                            adicionaNoInventario(escolhidoEST, Inventario, Pao_cima, Pao_baixo, Carne, Queijo_Suico, Ovo, Bacon, Mostarda, Ketchup, Alface, Tomate, Cebola, Cheddar, Picles); 
                            colocaNoHeapEstragado(enderecoDe(Inventario, Inventario.tamanho - 1), HEAP_PERECIVEIS, Turno);
                            imprime(Inventario); // temp
                            fpImprimir(HEAP_PERECIVEIS);// temp
                        }
                        if(escolhidoINV != -1) {
                            removeDoInventario(escolhidoINV, Inventario); 
                            reconstroiHeapDesatualizado(Inventario, HEAP_PERECIVEIS);
                            imprime(Inventario);// temp
                            fpImprimir(HEAP_PERECIVEIS);// temp
                        }
                        break;

                    case TELA_INVENTARIO:
                        int clicado;
                        if (AtualizarTelaInventario(telaInventario, clicado)) estado.tela = TELA_JOGO;        
                        break;  

                    case TELA_CORTE:
                        if (AtualizarTelaCorte(telaCorte)) estado.tela = TELA_JOGO; 
                        break;

                    case TELA_MONTAGEM:
                        if (AtualizarTelaMontagem(telaMontagem)) estado.tela = TELA_JOGO; 
                        break;
                }   

                switch (estado.tela) { // SWITCH CASE DE GRAFICOS

                    case TELA_JOGO:
                        DesenharMundo(fundo, blocos, jogador, animJogador, alvo, estado, Turno, Stamina);   // EM_JOGO
                        BotaoPassaTurno(Turno, Stamina, Inventario, HEAP_PERECIVEIS);
                    break;              

                    case TELA_FOGAO: {
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaFogao(telaFogao, Inventario);
                        desenhaPanelas(telaFogao.carnes, telaFogao.bocas, panela, carne_crua, carne_assada, carne_queimada, fogo, ovoFrito, ovo, baconFrito, bacon, TurnoAssado, cheddar, cheddarFrito, suico, suicoFrito, Turno);
                        break;
                    }
                    case TELA_ESTOQUE: 
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaEstoque(telaEstoque, Inventario);
                        break;
                    
                    case TELA_INVENTARIO: 
                        //ShowCursor();
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        DesenharTelaInventario(telaInventario, Inventario);
                        break;

                    case TELA_CORTE:
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        desenhaTelaMesaCorte(telaCorte, Inventario, texFaca, cebolaFeita, tomateFeito, Stamina, HEAP_PERECIVEIS);
                        break;

                    case TELA_MONTAGEM:
                        DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);  //Desenha o mundo para ficar bonito de fundo
                        desenhaTelaMontagem(telaMontagem, Inventario, tmp_img, HEAP_PERECIVEIS, Turno);    
                        break;
                }   
                break; //BREAK DO CASE GRANDE, NAO TIRAR (PARA MY PLISNO ASS)
            }

            case MENU: { // Caso o jogador esteja no menu

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                //ShowCursor();

                ClearBackground(WHITE); 
                DrawTexture(menu, 0, 0, WHITE);

                if(CheckCollisionPointRec(GetMousePosition(), btnIniciar)) {
                    DrawRectangleRounded(btnIniciar, 0.35f, 8, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador, Inventario, Turno, Stamina, HEAP_PERECIVEIS, HashPedidos, telaFogao, telaCorte);
                        EstadoPrograma = JOGANDO;
                    }
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnHistorico)) {
                    DrawRectangleRounded(btnHistorico, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = HISTORICO;
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnDificuldade)) {
                    DrawRectangleRounded(btnDificuldade, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = DIFICULDADE;
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnSair)) {
                    DrawRectangleRounded(btnSair, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        FechaJogo(animJogador, telaEstoque, menu, pausa, fundo, paoCima, paoBaixo, cheddar, suico, carne_crua, alface, tomate, ketchup, mostarda, cebola, ovo, bacon, picles);
                } 
                if(CheckCollisionPointRec(GetMousePosition(), btnComoJogar)) {
                    DrawRectangleRounded(btnComoJogar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = COMO_JOGAR;
                }
                break;
            }

            case PAUSADO: { // Caso o jogador tenha pausado

                SetExitKey(KEY_NULL); // Nao deixa que ele saia com esc
                if(IsKeyPressed(KEY_ESCAPE)) 
                    EstadoPrograma = JOGANDO;

                //ShowCursor();
                DesenharMundo(fundo, blocos, jogador, animJogador, nullptr, estado, Turno, Stamina);   // PAUSADO
                DrawRectangle(0, 0, LARGURA, ALTURA, Color{ 0, 0, 0, 167 });   // película preta translúcida
                DrawTexture(pausa, 420, 140, WHITE);

                if(CheckCollisionPointRec(GetMousePosition(), pausaVoltar)) {
                    DrawRectangleRounded(pausaVoltar, 0.4f, 4, ColorAlpha(LIGHTGRAY, 0.5f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        EstadoPrograma = JOGANDO;
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(), pausaReiniciar)) {
                    DrawRectangleRounded(pausaReiniciar, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        ReiniciarJogo(jogador, estado, animJogador, Inventario, Turno, Stamina, HEAP_PERECIVEIS, HashPedidos, telaFogao, telaCorte);
                        EstadoPrograma = JOGANDO;
                    }
                }
                if(CheckCollisionPointRec(GetMousePosition(), pausaMenu)) {
                    DrawRectangleRounded(pausaMenu, 0.4f, 4, Fade(LIGHTGRAY, 0.4f));
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        EstadoPrograma = MENU;
                }
                break;
            }

            case FIM_JOGO: {
                ClearBackground(BLACK); 

                if (telaDigitarNome(nome, pontuacao)) {
                    Historico novo = {nome, pontuacao};
                    salvaPontuacao("DadoBurguer/Arquivos/historico.txt", novo);   // append no arquivo
                    historico.push_back(novo);
                    mergeSort(historico);
                    if(IsKeyPressed(KEY_ENTER)) { 
                        EstadoPrograma = MENU;
                        nome.clear();
                    }
                }
                break;
            }
            
            case HISTORICO: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
                break;
            }

            case DIFICULDADE: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
                break;
            }

            case COMO_JOGAR: {
                ClearBackground(GREEN);
                if(GetCharPressed() > 0)
                    EstadoPrograma = MENU;
                DrawText("MANUTENCAO", 200, 200, 100, BLACK);
                DrawText("CLIQUE QUALQUER COISA PRA SAIR", 200, 400, 50, BLACK);
                break;
            }
        } // Fim switch telas

    mouseEscala = ((float)(((int)(GetTime() * 100) % 120)+1) / 60);          // Gera de 1/60 até 2
    mouseEscala = (mouseEscala > 1.0f)? 2.0f - mouseEscala : mouseEscala;
    mouseLarg = (mouse.width) * mouseEscala;
    mouseDestRect = {mousePos.x - (mouseLarg/2), mousePos.y - (mouse.height/2), mouseLarg, (float) mouse.height};
    DrawTexturePro(mouse, mouseRect, mouseDestRect, (Vector2) {0.0f, 0.0f}, 0.0f, WHITE);

    if(IsKeyPressed(KEY_ONE)) renderTeste = !renderTeste;
    if (renderTeste){
                if(IsKeyPressed(KEY_A)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::ALFACE, tmp_img);
                if(IsKeyPressed(KEY_N)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::CARNE, tmp_img);
                if(IsKeyPressed(KEY_U)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::CARNE_ASSADA, tmp_img);
                if(IsKeyPressed(KEY_T)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::TOMATE, tmp_img);
                if(IsKeyPressed(KEY_Q)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::CHEDDAR, tmp_img);
                if(IsKeyPressed(KEY_X)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::PAO_BAIXO, tmp_img);
                if(IsKeyPressed(KEY_S)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::SUICO, tmp_img);
                if(IsKeyPressed(KEY_K)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::KETCHUP, tmp_img);
                if(IsKeyPressed(KEY_M)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::MOSTARDA, tmp_img);
                if(IsKeyPressed(KEY_P)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::PICLES, tmp_img);
                if(IsKeyPressed(KEY_C)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::CEBOLA, tmp_img);
                if(IsKeyPressed(KEY_O)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::OVO, tmp_img);
                if(IsKeyPressed(KEY_L)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::CARNE_QUEIMADA, tmp_img);
                if(IsKeyPressed(KEY_Z)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::PAO_CIMA, tmp_img);
                if(IsKeyPressed(KEY_B)) Montagem::adicionarIngrediente(hamburguer, Ingredientes::BACON, tmp_img);
                if(IsKeyPressed(KEY_ZERO)) Montagem::removerIngrediente(hamburguer, tmp_img);
        DrawTexture(telaRenderTeste, 0, 0, WHITE);
        DrawTexture(hamburguer.textura, 250, 300, WHITE);
    }
    //DrawTexture(hamburguer.textura, 400, 50, WHITE);
    EndDrawing();
    }

    for (size_t i = 0; i < blocos.size(); i++)
        if (blocos[i].textura.id != 0) 
            UnloadTexture(blocos[i].textura);

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
    UnloadTexture(mouse);

    //UnloadTexture(txt);
    //UnloadTexture(txt2);
    UnloadTexture(telaRenderTeste);
    UnloadTexture(hamburguer.textura);
    UnloadImage(hamburguer.image);

    CloseWindow();

    return 0;
}