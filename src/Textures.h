#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"


class Textures{
    public:
    static Textures *GetTextures();
    static void FreeTextures();
    void AddTexture();
    void TextureFromImageLoad(int index, std::string filename, const SDL_Rect *source,const SDL_Rect *dest);
    void EndTexture(int index);
    void Draw(int index, SDL_Rect *source,SDL_Rect *dest);
    
    private:
    Textures(){};
    static Textures *textures_;
    SDL_Rect rectangle_;
    std::vector<SDL_Texture*> texture_;
    bool success_ = true;
};
#endif