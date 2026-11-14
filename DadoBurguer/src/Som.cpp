#include "Som.hpp"
#include <iostream>

/*SFX_PACK::SFX_PACK(const std::string folder, const std::string extension){
        path = folder;
        ext = extension;

        std::string aux;

        aux = folder;   background = LoadSound(aux.append("background").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   corte = LoadSound(aux.append("corte").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   correto = LoadSound(aux.append("correto").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   errado = LoadSound(aux.append("errado").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   fogao = LoadSound(aux.append("fogao").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   ronald = LoadSound(aux.append("ronald").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   tony = LoadSound(aux.append("tony").append(extension).c_str()); std::cout << aux << "\n";
    }
    SFX_PACK::SFX_PACK(){ SFX_PACK(SFX_defaultPath, SFX_defaultExtension); }*/

void SFX_PACK::UnloadPack() {
    if (IsMusicStreamPlaying(background)) StopMusicStream(background);
    UnloadMusicStream(background);

    if (IsSoundPlaying(corte)) StopSound(corte);
    UnloadSound(corte);

    if (IsSoundPlaying(correto)) StopSound(correto);
    UnloadSound(correto);

    if (IsSoundPlaying(errado)) StopSound(errado);
    UnloadSound(errado);

    if (IsSoundPlaying(fogao)) StopSound(fogao);
    UnloadSound(fogao);

    if (IsSoundPlaying(ronald)) StopSound(ronald);
    UnloadSound(ronald);

    if (IsSoundPlaying(tony)) StopSound(tony);
    UnloadSound(tony);
    }

void SFX_PACK::LoadPack(const std::string folder, const std::string extension){
        path = folder;
        ext = extension;

        std::string aux;

        aux = folder;   background = LoadMusicStream(aux.append("background").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   corte = LoadSound(aux.append("corte").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   correto = LoadSound(aux.append("correto").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   errado = LoadSound(aux.append("errado").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   fogao = LoadSound(aux.append("fogao").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   ronald = LoadSound(aux.append("ronald").append(extension).c_str()); std::cout << aux << "\n";
        aux = folder;   tony = LoadSound(aux.append("tony").append(extension).c_str()); std::cout << aux << "\n";
    }