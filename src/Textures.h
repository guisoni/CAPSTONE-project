#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class Textures{
    public:
    static Textures *GetTextures();
    static void FreeTextures();
    void TextureFromImageLoad(std::string filename);
    void EndTexture();
    
    private:
    static Textures *textures_;
    SDL_Rect rectangle_;
    SDL_Texture *texture_=nullptr;
    bool success_ = true;
};
#endif