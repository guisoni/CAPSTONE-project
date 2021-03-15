#ifndef Core_H
#define Core_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Physics.h"
#include <limits>
enum PlanetsEnum{KMERCURY,KVENUS, KEARTH, KMOON, KMARS, KJUPITER, KSATURN, KURANUS, KNEPTUNE, KPLUTO, KSUN};
class Core{
    public: 
    static Core *GetCore();

    static void FreeCore();

    void Start();
    
    void RunGame();

    void EndGraphics();

    void Renderer();

    bool GetStatus(){return success_;}
    SDL_Renderer * GetRenderer(){return sdl_renderer_;}
    
    void ClearRenderer();

    void EventHandler();
    
    void multiplyDelta(int multiply){
        if(multiply * delta_ >=1 && multiply*delta_ <= std::numeric_limits<int>::max() ){
            delta_ *= multiply;
        }
    }
    private:
    Core(){};
    static Core *core_;
    bool success_ = true;
    SDL_Window* sdl_window_ = nullptr;
    SDL_Renderer* sdl_renderer_ = nullptr;
    SDL_Texture* texture_= nullptr;
    const int screen_width_{1820};
    const int screen_height_{780};
    const std::size_t framesPerSecond_{60};
    const std::size_t msPerFrame_{1000 / framesPerSecond_};
    std::size_t timeRatio_{1};
    PlanetsEnum cameraId_ = KSUN;
    double scale_factor_= 10000;
    Vector2Elm displ_ = {0,0};
    Vector2Elm vel_ = {0  ,-11190/700000000};
    int delta_= 1;
    const int minBodySize_ = 4;
    bool isLocked_ = false;
    const double minimumScaleFactor_ = 7.45058E-05;
    const double maximumScaleFactor_ = 10240000.;
};
#endif

