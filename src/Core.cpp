#ifndef Core_H
#define Core_H

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
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
        std::cout<<"Core Ended\n";
        delete core_;
    }
    void Start(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL could not initialize.\n";
            std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
            success_ = false;
        }else{
            std::cout << "SDL initialized.\n";
            // Create Window
            sdl_window_ = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, screen_width,
                screen_height, SDL_WINDOW_SHOWN);
            if (sdl_window_==nullptr) {
                std::cerr << "Window could not be created.\n";
                std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
                success_ = false;
            }else{
                std::cout << "Window allocated.\n";
                // Create renderer
                sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
                if (sdl_renderer_== nullptr) {
                    std::cerr << "Renderer could not be created.\n";
                    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
                    success_ = false;
                }else{
                    std::cout << "renderer allocated.\n";
				    //Default renderer color
				    SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
				    //Create PNG loading
				    int flags = IMG_INIT_JPG|IMG_INIT_PNG;
				    if( (IMG_Init( flags ) & flags)  != flags )
				    {
                        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n"; 
					    success_ = false;
				    }
                }
            }
        }
    }    
    void End(){
        if(sdl_window_ != nullptr){
            SDL_DestroyWindow(sdl_window_);
            std::cout << "Window destroyed.\n";    
        }
        std::cout << "Quit SDL.\n";
        SDL_Quit();
    }
    void Renderer(){
	    //Load PNG image
        std::string path = "../image/EARTH1.png";
	    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	    if( loadedSurface == NULL )
	    {
		    std::cerr<< "Image " << path.c_str() << " not loaded! SDL_image Error: "<< IMG_GetError()<<"\n";
            success_ = false;
	    }else{
        	//Create texture from surface pixels
            texture_ = SDL_CreateTextureFromSurface( sdl_renderer_, loadedSurface );
	        if( texture_ == nullptr )
	        {
               std::cerr<< "Texture from Image " << path.c_str() << " not created! SDL_image Error: "<< IMG_GetError()<<"\n";
               success_ = false;
	        }
        }
		//Delete loaded surface
		SDL_FreeSurface( loadedSurface );
        //Clear screen
		SDL_RenderClear( sdl_renderer_ );
		//Render texture to screen
		SDL_RenderCopy( sdl_renderer_, texture_, NULL, NULL );
		//Update screen
		SDL_RenderPresent( sdl_renderer_ );
	}
    void EventHandler(){
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                success_ = false;
            }else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        success_ = false;
                        break;
                }
            }    
        }
    }

    bool GetStatus(){return success_;}
    private:
    Core(){};
    static Core *core_;
    bool success_ = true;
    SDL_Window* sdl_window_ = nullptr;
    SDL_Renderer* sdl_renderer_ = nullptr;
    SDL_Texture* texture_= nullptr;
    size_t screen_width{640};
    size_t screen_height{640};
    
};
#endif

Core* Core::core_= nullptr;
int main(){
    Core::GetCore();
    Core::GetCore()->Start();
    while(Core::GetCore()->GetStatus()){
        Core::GetCore()->Renderer();
        Core::GetCore()->EventHandler();
    }
    Core::GetCore()->End();
    Core::FreeCore();
}

