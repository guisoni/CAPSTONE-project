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
    void End(){
        if(texture_ != nullptr){
            SDL_DestroyTexture( texture_ );
            texture_ = nullptr;
            std::cout << "Texture destroyed.\n";
        }

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
        if(texture_ != nullptr){
            SDL_DestroyTexture( texture_ );
        texture_ = nullptr;
        }
	    //Load PNG image
        std::string path = "../image/EARTH2.png";
	    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	    if( loadedSurface == NULL )
	    {
		    std::cerr<< "Image " << path.c_str() << " not loaded! SDL_image Error: "<< IMG_GetError()<<"\n";
            success_ = false;
	    }else{
            //Set a color to be transparent
		    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 119, 236, 255 ) );

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
        //Set rendering space and render to screen
	    SDL_Rect imageQuad = { 0, 0, 600, 600 };
        SDL_Rect renderQuad = { 0, 0, 300, 300 };
        //Render texture to screen
		SDL_RenderCopy( sdl_renderer_, texture_, NULL, &renderQuad );
        
        /*//Modulate color rgb
           Uint8 red = 0, green = 65, blue = 30;
	       if(SDL_SetTextureColorMod( texture_, red, green, blue ) < 0){
               std::cerr<<"Color modulation not suported! SDL Error: " << SDL_GetError()<<"\n";
           }else{
               Uint8 *pred, *pgreen, *pblue; 
               SDL_GetTextureColorMod( texture_, pred, pgreen, pblue );
               std::cout<<"Modulation of: "<< *pred <<", "<< *pgreen <<", "<< *pblue <<", "<< "\n";
           }*/

           /*//Set blending function
           SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND; //NONE, ADD, BLEND, MOD
	       if(SDL_SetTextureBlendMode( texture_, blendMode )<0){
               std::cerr<<"Blending not suported! SDL Error: " << SDL_GetError()<<"\n";
           }else{
               SDL_BlendMode *pblendMode;
               SDL_GetTextureBlendMode( texture_, pblendMode );
               std::cout<<"Blend Mode: "<< *pblendMode <<", "<< "\n";
           }
	       //Modulate opacity (alpha)
           Uint8 alpha = 100;
	       if(SDL_SetTextureAlphaMod( texture_, alpha )<0){
               std::cerr<<"AlphaMod not suported! SDL Error: " << SDL_GetError()<<"\n";
           }else{
               Uint8 *palpha;
               SDL_GetTextureAlphaMod( texture_, palpha );
               std::cout<<"Blend Mode: "<< *palpha <<", "<< "\n";
           }*/


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
    size_t screen_width{1820};
    size_t screen_height{780};
    
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

