#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Core.h"
#include "Physics.h"
#include "Textures.h"

Core *Core::GetCore(){
    if(core_ == nullptr){
        core_= new Core(); 
        std::cout<<"Core Started\n"; 
        return core_;
    }
    return core_;
}        
void Core::FreeCore(){
    std::cout<<"Core Ended\n";
    delete core_;
}
void Core::Start(){
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
        SDL_WINDOWPOS_CENTERED, screen_width_,
        screen_height_, SDL_WINDOW_SHOWN);
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
    
void Core::RunGame(double dt){
    
    for(int index = 0; index < SolarSystem::GetSolarSystem()->GetNumberOfBodies();index++){
        Textures::GetTextures()->AddTexture();
        std::string filename = SolarSystem::GetSolarSystem()->GetBody(index)->GetName();
        SDL_Point position;
        int width = 60;
        int height = 60;
        position.x = static_cast<int>(screen_width_/2+SolarSystem::GetSolarSystem()->GetBody(index)->GetPosition().x_-width/2);
        position.y = static_cast<int>(screen_height_/2-SolarSystem::GetSolarSystem()->GetBody(index)->GetPosition().y_+height/2);
        SDL_Rect source = {position.x,position.y,width,height};
        SDL_Rect dest = source;
        Textures::GetTextures()->TextureFromImageLoad(index,"../image/" + filename + ".png", NULL, &dest);
    }
    int count = 0;
    
    while(Core::GetCore()->GetStatus()){
        count++;
        Core::GetCore()->ClearRenderer();
        if(count == 100){
        for(int index = 0; index < SolarSystem::GetSolarSystem()->GetNumberOfBodies();index++){
            SDL_Point pixelposition;
            int width = 60;
            int height = 60;
            Vector2Elm position;
            position = SolarSystem::GetSolarSystem()->GetBody(index)->Transform(SolarSystem::GetSolarSystem()->GetBody(10));
            position.LogarithmScale();
            pixelposition.x = static_cast<int>(screen_width_/2 + position.x_*20-width/2);
            pixelposition.y = static_cast<int>(screen_height_/2 - position.y_*20+height/2);

            

            //position.x = static_cast<int>(screen_width_/2+SolarSystem::GetSolarSystem()->GetBody(index)->GetPosition().x_-width/2);
            //position.y = static_cast<int>(screen_height_/2-SolarSystem::GetSolarSystem()->GetBody(index)->GetPosition().y_+height/2);
            SDL_Rect source = {pixelposition.x,pixelposition.y,width,height};
            SDL_Rect dest = source;
            Textures::GetTextures()->Draw(index,NULL, &dest);
            count = 0;
        }
        
        Core::GetCore()->Renderer();
        }
        Core::GetCore()->EventHandler();  
        SolarSystem::GetSolarSystem()->Update(dt);
        //SolarSystem::GetSolarSystem()->PrintBody(2);
    }
    for(int index = 0; index < SolarSystem::GetSolarSystem()->GetNumberOfBodies();index++){
        Textures::GetTextures()->EndTexture(index);
    }
}
void Core::EndGraphics(){
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

void Core::Renderer(){
	SDL_RenderPresent( sdl_renderer_ );
}
void Core::ClearRenderer(){
    SDL_RenderClear( sdl_renderer_ );
}
void Core::EventHandler(){
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




