#ifndef Core_H
#define Core_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
class Core{
    public: 
    static Core *GetCore();

    static void FreeCore();

    void Start();
    
    void RunGame(double dt);

    void EndGraphics();

    void Renderer();

    bool GetStatus(){return success_;}
    SDL_Renderer * GetRenderer(){return sdl_renderer_;}
    
    void ClearRenderer();

    void EventHandler();

    private:
    Core(){};
    static Core *core_;
    bool success_ = true;
    SDL_Window* sdl_window_ = nullptr;
    SDL_Renderer* sdl_renderer_ = nullptr;
    SDL_Texture* texture_= nullptr;
    int screen_width_{1820};
    int screen_height_{780};
    
};
#endif

