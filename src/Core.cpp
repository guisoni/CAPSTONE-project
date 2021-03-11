#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Core.h"
#include "Physics.h"
#include "Textures.h"
#include <limits>
#include <iomanip>
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
    
void Core::RunGame(){ 
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    std::size_t target_frame_duration = msPerFrame_;
    int frame_count = 0;
    double dt;
    dt = 876*10; 
    
    for(int index = 0; index < SolarSystem::GetSolarSystem()->GetNumberOfBodies();index++){
        Textures::GetTextures()->AddTexture();
        std::string filename = SolarSystem::GetSolarSystem()->GetBody(index)->GetName();
        std::cout << filename <<"\n";
        Textures::GetTextures()->TextureFromImageLoad(index,"../image/" + filename + ".png");
        SDL_Rect source{0,0,0,0};
        Textures::GetTextures()->GetTextureSize(index, source);
        double diameter = SolarSystem::GetSolarSystem()->GetBody(index)->GetDiameter();
        Textures::GetTextures()->AddScaleFactor(source.w, diameter);
        
        
    }
    while(Core::GetCore()->GetStatus()){
        frame_start = SDL_GetTicks();
        Core::GetCore()->ClearRenderer();
        
        //load textures to use
            for(int index = 0; index < SolarSystem::GetSolarSystem()->GetNumberOfBodies();index++){
                SDL_Point pixelposition;
                Vector2Elm position;
                //displ_ = displ_+ vel_* dt;
                position = SolarSystem::GetSolarSystem()->GetBody(index)->Transform(SolarSystem::GetSolarSystem()->GetBody(cameraId_));
                double R = SolarSystem::GetSolarSystem()->GetBody(cameraId_)->GetDiameter()/2*scale_factor_;
                
                position.x_ = position.x_  - SolarSystem::GetSolarSystem()->GetBody(cameraId_)->GetDiameter()/2;
                //position.LogarithmScale();
                ImgPosScale imgData = SolarSystem::GetSolarSystem()->GetBody(index)->GetImgData();
                //std::cout<<imgData.X()<<", "<<imgData.Y() << "\n";
                //std::cout<<position.x_<<" "<<position.y_ << "\n";
                position.x_ = ((position.x_+ imgData.X()) * scale_factor_)- displ_.x_;
                position.y_ = ((position.y_+ imgData.Y()) * scale_factor_)- displ_.y_;
                //std::cout<<position.x_<<" "<<position.y_ << "\n";
                SDL_Rect source = {0, 0, 0, 0}; 
                Textures::GetTextures()->GetTextureSize(index, source);
                std::cout<<source.w<<"\n";
                double scalex = Textures::GetTextures()->GetScaleFactor(index);
                double scaley = Textures::GetTextures()->GetScaleFactor(index);
                source.w = static_cast<int>(source.w*(scale_factor_*scalex*imgData.ScaleWidth()));
                source.w = (source.w <= 4)? 4:source.w; 
                source.h = static_cast<int>(source.h*(scale_factor_*scaley*imgData.ScaleHeight())); 
                source.h = (source.h <= 4)? 4:source.h;
                SDL_Rect dest = source;
                long max_pos_x = std::numeric_limits<int>::max()-screen_width_/2.0 + source.w/2.0;
                long max_pos_y = std::numeric_limits<int>::max() + screen_height_/2.0 - source.h/2.0;
                if(AuxMath::abs(position.x_) <= max_pos_y && AuxMath::abs(position.y_) <= max_pos_y){  
                    pixelposition.x = static_cast<int>(screen_width_/2.0 + position.x_- source.w/2.0 );
                    pixelposition.y = static_cast<int>(screen_height_/2.0 - position.y_ - source.h/2.0);
                    dest.x = pixelposition.x;
                    dest.y = pixelposition.y;
                    Textures::GetTextures()->Draw(index,NULL, &dest);
                    SDL_SetRenderDrawColor( sdl_renderer_, 0xFF, 0x00, 0xFF, 0xFF );
                    SDL_RenderDrawPoint( sdl_renderer_, screen_width_/2, screen_height_/2 );
                    SDL_RenderDrawPoint( sdl_renderer_, screen_width_/2+static_cast<int>(R), screen_height_/2 );
                    SDL_RenderDrawPoint( sdl_renderer_, screen_width_/2-static_cast<int>(R), screen_height_/2 );
                    SDL_RenderDrawPoint( sdl_renderer_, screen_width_/2, screen_height_/2-static_cast<int>(R) );
                    SDL_RenderDrawPoint( sdl_renderer_, screen_width_/2, screen_height_/2+static_cast<int>(R) );
                    std::cout<< std::setprecision(15) << displ_.x_ <<" "<<std::setprecision(15)<<displ_.y_<<" " << delta_<<"\n";
                }   
        }
                
        Core::GetCore()->Renderer();
        Core::GetCore()->EventHandler();  
        int iteractions = 0;
        while(iteractions < timeRatio_){
            SolarSystem::GetSolarSystem()->Update(dt);
            iteractions++;
        }
        iteractions = 0;
        //SolarSystem::GetSolarSystem()->PrintBody(2);
        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;


        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }else{
                if(timeRatio_>=2){
                    timeRatio_ -= 1;
                }
            if (frame_end - title_timestamp >= 1000) {
                frame_count = 0;
                //std::cout<<"Time Ratio " <<timeRatio_*dt<<"\n";
                title_timestamp = frame_end;
            }
        }

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
    SDL_SetRenderDrawColor( sdl_renderer_, 0, 0, 0, 0 );
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
                case SDLK_1:
                    cameraId_ = KMERCURY;
                    displ_ = {0,0};
                    break;
                case SDLK_2:
                    cameraId_ = KVENUS;
                    displ_ = {0,0};
                    break;  
                case SDLK_3:
                    cameraId_ = KEARTH;
                    displ_ = {0,0};
                    break;  
                case SDLK_4:
                    cameraId_ = KMOON;
                    displ_ = {0,0};
                    break;  
                case SDLK_5:
                    cameraId_ = KMARS;
                    displ_ = {0,0};
                    break;  
                case SDLK_6:
                    cameraId_ = KJUPITER;
                    displ_ = {0,0};
                    break;  
                case SDLK_7:
                    cameraId_ = KSATURN;
                    displ_ = {0,0};
                    break;  
                case SDLK_8:
                    cameraId_ = KURANUS;
                    displ_ = {0,0};
                    break;  
                case SDLK_9:
                    cameraId_ = KNEPTUNE;
                    displ_ = {0,0};
                    break;  
                case SDLK_0:
                    cameraId_ = KPLUTO;
                    displ_ = {0,0};
                    break;  
                case SDLK_s:
                    cameraId_ = KSUN;
                    displ_ = {0,0};
                break;
                case SDLK_z:
                     if(scale_factor_ <= 2000000000){
                         scale_factor_ *= 2;
                         displ_ = displ_*2;
                     }
                     break;
                case SDLK_x:
                     if(scale_factor_ >= 0.000000000001){
                         scale_factor_ /= 2;
                         displ_ =displ_/2; 
                     }
                     break;
                case SDLK_UP:
                    displ_.y_+= delta_;
                    break;
                case SDLK_DOWN:
                    displ_.y_ -= delta_;
                    break;
                case SDLK_LEFT:
                    displ_.x_ -= delta_;
                    break;
                case SDLK_RIGHT:
                    displ_.x_ += delta_;
                    break;
                case SDLK_j:
                    delta_ *= 2;
                    break;
                case SDLK_m:
                    delta_ /= 2;
                    break;
                    

            }
        }    
    }
}




