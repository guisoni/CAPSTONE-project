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
    void AddScaleFactor(const int &refmeasure, const double &Diam);
    void TextureFromImageLoad(int index, std::string filename);
    void EndTexture(int index);
    void Draw(int index, SDL_Rect *source,SDL_Rect *dest,double angle,SDL_Point * center, SDL_RendererFlip flip);
    int GetTextureSize(int id, SDL_Rect &textRect);
    double GetScaleFactor(int index){return scale_texture_.at(index);}
    
    private:
    Textures(){};
    static Textures *textures_;
    SDL_Rect rectangle_;
    std::vector<SDL_Texture*> texture_;
    std::vector<double> scale_texture_;
    bool success_ = true;
};
#endif