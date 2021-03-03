#ifndef Core_H
#define Core_H

#include <iostream>

#include "SDL2/SDL.h"
class Core{
    public: 
     static Core *GetCore(){
        if(core_ == nullptr){
            core_= new Core(); 
            std::cout<<"Core Started\n"; 
            return core_;
        }
        return core_;
    }        
    static void FreeCore(){
        std::cout<<"Core Deleted\n";
        delete core_;
    }
    void Start(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            success_ = false;
        }else{
            std::cout << "SDL initialized.\n";
        }
    }
    void End(){
        std::cout << "Quit SDL.\n";
        SDL_Quit();
    }

    private:
    Core(){};
    static Core *core_;
    bool success_ = true;
};
#endif

Core* Core::core_= nullptr;
int main(){
    Core::GetCore();
    Core::FreeCore();
    Core::GetCore()->Start();
    Core::GetCore()->End();
}

