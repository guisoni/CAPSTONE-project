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
              //Set texture filtering to linear
		      if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		      {
			       std::cerr << "Warning: Linear texture filtering not enabled!\n";
		    }
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
				    SDL_SetRenderDrawColor( sdl_renderer_, 0, 0, 0, 0 );
				    //Create PNG loading
				    int flags = IMG_INIT_JPG;//|IMG_INIT_PNG;
				    if( (IMG_Init( flags ) & flags)  != flags )
				    {
                        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << "\n"; 
					    success_ = false;
				    }
                }
            }
        }
    }    
    
    void EndGraphics(){
            if(sdl_renderer_ != nullptr){
            SDL_DestroyRenderer( sdl_renderer_ );
            sdl_renderer_ = nullptr;
            std::cout << "Texture destroyed.\n";
        }
        if(sdl_window_ != nullptr){
            SDL_DestroyWindow(sdl_window_);
            std::cout << "Window destroyed.\n";    
        }
        std::cout << "Quit Image.\n";
        IMG_Quit();

        std::cout << "Quit SDL.\n";
        SDL_Quit();

    }

    void Renderer(){
		SDL_RenderPresent( sdl_renderer_ );
	}
    void ClearRenderer(){
        SDL_RenderClear( sdl_renderer_ );
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
    SDL_Renderer * GetRenderer(){return sdl_renderer_;}
    private:
    Core(){};
    static Core *core_;
    bool success_ = true;
    SDL_Window* sdl_window_ = nullptr;
    SDL_Renderer* sdl_renderer_ = nullptr;
    SDL_Texture* texture_= nullptr;
    size_t screen_width{1820};
    size_t screen_height{780};
    
};
#endif

#ifndef TEXTURES.H
#define TEXTURES.H

//#include <iostream>
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"


class Textures{
    public:
     static Textures *GetTextures(){
        if(textures_ == nullptr){
            textures_= new Textures(); 
            std::cout<<"Textures Started\n"; 
            return textures_;
        }
        return textures_;
    }        
    static void FreeTextures(){
        std::cout<<"Textures Ended\n";
        delete textures_;
    }
     void TextureFromImageLoad(std::string filename){
		//Update screen 
        if(texture_ != nullptr){
            SDL_DestroyTexture( texture_ );
        texture_ = nullptr;
        }
	    //Load PNG image
	    SDL_Surface* loadedSurface = IMG_Load(filename.c_str() );
	    if( loadedSurface == NULL )
	    {
		    std::cerr<< "Image " << filename.c_str() << " not loaded! SDL_image Error: "<< IMG_GetError()<<"\n";
            success_ = false;
	    }else{
            //Set a color to be transparent
		    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 119, 236, 255 ) );

        	//Create texture from surface pixels
            texture_ = SDL_CreateTextureFromSurface( Core::GetCore()->GetRenderer(), loadedSurface );
	        if( texture_ == nullptr )
	        {
               std::cerr<< "Texture from Image " << filename.c_str() << " not created! SDL_image Error: "<< IMG_GetError()<<"\n";
               success_ = false;
	        }
            //Set rendering space and render to screen
	        SDL_Rect imageRect = { 0, 0, 600, 600 };
            SDL_Rect renderRect = { 0, 0, 300, 300 };
            //Render texture to screen
		    SDL_RenderCopy( Core::GetCore()->GetRenderer(), texture_, &imageRect, &renderRect );
        }
		//Delete loaded surface
		SDL_FreeSurface( loadedSurface );
        //Clear screen
     }
     void EndTexture(){
            if(texture_ != nullptr){
                SDL_DestroyTexture( texture_ );
                texture_ = nullptr;
                std::cout << "Texture destroyed.\n";

        }

     }
    private:
    static Textures *textures_;
    SDL_Rect rectangle_;
    SDL_Texture *texture_=nullptr;
    bool success_ = true;
};
#endif

Core* Core::core_= nullptr;
Textures* Textures::textures_=nullptr;
int main(){
    Core::GetCore();
    Core::GetCore()->Start();
    while(Core::GetCore()->GetStatus()){
        Core::GetCore()->ClearRenderer();
        Textures::GetTextures()->TextureFromImageLoad("../image/EARTH1.png");
        Core::GetCore()->Renderer();
        Core::GetCore()->EventHandler();
    }
    Textures::GetTextures()->EndTexture();
    Core::GetCore()->EndGraphics();
    Core::FreeCore();
}

