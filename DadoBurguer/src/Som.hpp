#pragma once

#include "raylib.h"
#include <string>

const std::string SFX_defaultPath = "DadoBurguer/assets/som/default/";
const std::string SFX_defaultExtension = ".mp3";

struct SFX_PACK {
    std::string path;
    std::string ext;
    Music background;
    Sound corte;
    Sound correto;
    Sound errado;
    Sound fogao;
    Sound ronald;
    Sound tony;

    //SFX_PACK(const std::string folder, const std::string extension);
    //SFX_PACK();
    void LoadPack(const std::string folder, const std::string extension);
    //~SFX_PACK();
    void UnloadPack();
};