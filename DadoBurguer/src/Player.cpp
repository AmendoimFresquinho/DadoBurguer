#include "raylib.h"
#include "raymath.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include <cfloat>
#include <vector>

const int ANIM_LARGURA_FRAME = 32;
const int ANIM_ALTURA_FRAME = 32;
const int ANIM_FRAMES_POR_DIRECAO = 4;
const float ANIM_TEMPO_POR_FRAME = 0.125f;   

void Movimentacao(Jogador& player) {
    Vector2 direction = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_D)) direction.x += 1.0f;
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;  
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;

    if (Vector2LengthSqr(direction) > 0.0f) direction = Vector2Normalize(direction);

    player.aceleracao = Vector2Scale(direction, player.velocidade);
}

Rectangle HitBox(const Jogador& p) {
    return { p.posicao.x - p.larguraHit / 2, p.posicao.y - p.alturaHit / 2, p.larguraHit, p.alturaHit };
}

void Colisoes(Jogador& player, float dt, const std::vector<Rectangle>& solids) {

    player.posicao.x += player.aceleracao.x * dt;        
    Rectangle r = HitBox(player);  

    for (size_t i = 0; i < solids.size(); i++) {
        const Rectangle& s = solids[i];
        if (!CheckCollisionRecs(r, s)) continue;         

        if (player.aceleracao.x > 0)                       
            player.posicao.x = s.x - player.larguraHit / 2;
        else if (player.aceleracao.x < 0)                  
            player.posicao.x = s.x + s.width + player.larguraHit / 2;

        r = HitBox(player);                          
    }

    player.posicao.y += player.aceleracao.y * dt;
    r = HitBox(player);
    
    for (size_t i = 0; i < solids.size(); i++) {
        const Rectangle& s = solids[i];
        if (!CheckCollisionRecs(r, s)) continue;

        if (player.aceleracao.y > 0)                       
            player.posicao.y = s.y - player.alturaHit / 2;
        else if (player.aceleracao.y < 0)                  
            player.posicao.y = s.y + s.height + player.alturaHit / 2;

        r = HitBox(player);
    }
}

Bloco* ProcuraInteragir(const Jogador& player, std::vector<Bloco>& blocks, float reach) {
    Rectangle pr = HitBox(player);
    Bloco* closest = nullptr;
    float bestDist = FLT_MAX;

    for (size_t i = 0; i < blocks.size(); i++) {
        Bloco& b = blocks[i];
        if (!b.interage) continue;

        Rectangle area = { b.rect.x - reach, b.rect.y - reach, b.rect.width + 2 * reach, b.rect.height + 2 * reach };
        if (!CheckCollisionRecs(pr, area)) continue;

        Vector2 center = { b.rect.x + b.rect.width / 2, b.rect.y + b.rect.height / 2 };
        float dist = Vector2LengthSqr(Vector2Subtract(player.posicao, center));
        if (dist < bestDist) { bestDist = dist; closest = &b; }
    }

    return closest;
}

void FazInteracao(const Bloco& bloco, EstadoJogo& estado) {
    switch (bloco.acao) {
        case ABRIR_FOGAO: estado.tela = TELA_FOGAO; break;
        case ACAO_ABRIR_ESTOQUE: estado.tela = TELA_ESTOQUE; break;
        case ACAO_CORTAR: estado.tela = TELA_CORTE; break;
        case ACAO_ATENDER: estado.tela = TELA_ATENDER; break;
        case SEM_ACAO: break;
        case ACAO_ABRIR_INVENTARIO: estado.tela = TELA_ESTOQUE; break;
        case ACAO_MONTAR: estado.tela = TELA_MONTAGEM; break;
        default:
        break;
    }
}
 
AnimJogador CriarAnimJogador(const char* arquivo) {
    AnimJogador a;
    a.sheet = Texture2D();   // zerada: id == 0
    a.frame = 0;
    a.tempo = 0.0f;
    a.direcao = DIR_BAIXO;
 
    if (FileExists(arquivo)) {
        a.sheet = LoadTexture(arquivo);
        SetTextureFilter(a.sheet, TEXTURE_FILTER_POINT);   // pixel art sem borrão
    } else {
        TraceLog(LOG_WARNING, "Spritesheet nao encontrada: %s (pasta atual: %s)", arquivo, GetWorkingDirectory());
    }
    return a;
}
 
void DescarregarAnimJogador(AnimJogador& a) {
    if (a.sheet.id != 0) UnloadTexture(a.sheet);
}
 
void AtualizarAnimJogador(AnimJogador& a, Vector2 deslocamento, float dt) {
    bool andando = Vector2LengthSqr(deslocamento) > 0.01f;
 
    if (andando) {
        if (fabsf(deslocamento.x) > fabsf(deslocamento.y))
            a.direcao = (deslocamento.x > 0) ? DIR_DIREITA : DIR_ESQUERDA;
        else
            a.direcao = (deslocamento.y > 0) ? DIR_BAIXO : DIR_CIMA;
 
        a.tempo += dt;
        if (a.tempo >= ANIM_TEMPO_POR_FRAME) {
            a.tempo -= ANIM_TEMPO_POR_FRAME;
            a.frame = (a.frame + 1) % ANIM_FRAMES_POR_DIRECAO;
        }
    }   
    else {
        a.frame = 0;
        a.tempo = 0.0f;
    }
}
 
void DesenharAnimJogador(const AnimJogador& a, Rectangle hitbox) {
    if (a.sheet.id == 0) {                     
        DrawRectangleRec(hitbox, MAROON);
        return;
    }
 
    Rectangle origem = { (float)(a.frame * ANIM_LARGURA_FRAME), (float)((int)a.direcao * ANIM_ALTURA_FRAME), (float)ANIM_LARGURA_FRAME, (float)ANIM_ALTURA_FRAME };
 
    Rectangle destino = { roundf(hitbox.x), roundf(hitbox.y), hitbox.width, hitbox.height };
    DrawTexturePro(a.sheet, origem, destino, { 0, 0 }, 0.0f, WHITE);
}

