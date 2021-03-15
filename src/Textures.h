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
    void TextureFromImageLoad(const int &index, const std::string &filename);
    void EndTexture(const int &index);
    void Draw(const int &index, const SDL_Rect *source,const SDL_Rect *dest,const  double &angle,const SDL_Point * center,const SDL_RendererFlip &flip);
    int GetTextureSize(const int id, SDL_Rect &textRect) const;
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