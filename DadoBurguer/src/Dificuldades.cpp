#include "raylib.h"
#include "Funcoes.hpp"
#include "Structs.hpp"
#include "Constantes.hpp"
#include "Montagem.hpp"
#include <iostream>

int configuraDificuldadeStamina(Dificuldade &Dificuldade, int &Stamina){

    if(Dificuldade == FACIL) return STAMINA_FACIL;
    else if(Dificuldade == MEDIO) return STAMINA_MEDIO;
    else if(Dificuldade == DIFICIL) return STAMINA_DIFICIL;
    else return STAMINA_IMPOSSIVEL;

}

void telaDificuldade(Dificuldade &Dificuldade, Texture2D &tela, Texture2D &facil, Texture2D &medio, Texture2D &dificil, Texture2D &impossivel, int &processos){

    Vector2 mouse = GetMousePosition();
    
    Rectangle facilR = {405, 243, 465, 80}; 
    Rectangle medioR = {405, 333, 465, 80}; 
    Rectangle dificilR = {405, 423, 465, 80}; 
    Rectangle impossivelR = {405, 513, 465, 80}; 

    Vector2 facilV = {405, 243}; 
    Vector2 medioV = {405, 333}; 
    Vector2 dificilV = {405, 423}; 
    Vector2 impossivelV = {405, 513}; 

    DrawTexture(tela, 0,0, WHITE);

    if(Dificuldade == FACIL) DrawTextureEx(facil, facilV, 0.0f, 1.0f, WHITE);
    if(Dificuldade == MEDIO) DrawTextureEx(medio, medioV, 0.0f, 1.0f, WHITE);
    if(Dificuldade == DIFICIL) DrawTextureEx(dificil, dificilV, 0.0f, 1.0f, WHITE);
    if(Dificuldade == IMPOSSIVEL) DrawTextureEx(impossivel, impossivelV, 0.0f, 1.0f, WHITE);

    if(CheckCollisionPointRec(mouse, facilR)){
        DrawTextureEx(facil, facilV, 0.0f, 1.0f, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Dificuldade = FACIL;
        }
    }
    if(CheckCollisionPointRec(mouse, medioR)){
        DrawTextureEx(medio, medioV, 0.0f, 1.0f, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Dificuldade = MEDIO;
        }
    }
    if(CheckCollisionPointRec(mouse, dificilR)){
        DrawTextureEx(dificil, dificilV, 0.0f, 1.0f, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Dificuldade = DIFICIL;
        }
    }
    if(CheckCollisionPointRec(mouse, impossivelR)){
        DrawTextureEx(impossivel, impossivelV, 0.0f, 1.0f, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            Dificuldade = IMPOSSIVEL;
        }
    }
}

bool checaProcessos(int &processos, Dificuldade &dificuldade){

    if(dificuldade == FACIL && processos >= 5) return true;
    if(dificuldade == MEDIO && processos >= 4) return true;
    if(dificuldade == DIFICIL && processos >= 2) return true;
    if(dificuldade == IMPOSSIVEL && processos >= 1) return true;

    return false;

}