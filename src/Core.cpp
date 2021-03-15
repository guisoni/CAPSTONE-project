#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Core.h"
#include "Physics.h"
#include "Textures.h"
#include "PixelMath.h"
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
                std::shared_ptr<Body> thisBody =  SolarSystem::GetSolarSystem()->GetBody(index);
                std::shared_ptr<Body> refBody =  SolarSystem::GetSolarSystem()->GetBody(cameraId_);
                position = thisBody->GetPosition();
                position = position.Transform(refBody->GetPosition());
                double R = refBody->GetDiameter()/2.0;
                SDL_Rect source = {0, 0, 0, 0}; 
                Textures::GetTextures()->GetTextureSize(index, source);
                ImgPosScale imgData = thisBody->GetImgData();                
                double imgDataX= imgData.X();
                double imgDataY= imgData.Y();
                position.x_ = ((position.x_+ imgDataX) * scale_factor_)- displ_.x_;
                position.y_ = ((position.y_+ imgDataY)* scale_factor_)- displ_.y_;
                double angle =  thisBody->GetAngularPosition();
                if(isLocked_){
                    //transform in relation to the rotation of a planet  
                    position = position.RotationTransform(angle);
                }
                double scalex = Textures::GetTextures()->GetScaleFactor(index);
                double scaley = Textures::GetTextures()->GetScaleFactor(index);
                source.w = static_cast<int>(source.w*(scale_factor_*scalex*imgData.ScaleWidth()));
                source.w = (source.w <= minBodySize_)? minBodySize_:source.w; 
                source.h = static_cast<int>(source.h*(scale_factor_*scaley*imgData.ScaleHeight())); 
                source.h = (source.h <= minBodySize_)? minBodySize_:source.h;
                SDL_Rect dest = source;
                SDL_Point center; 
                if(PixelMath::ConvertPositionToPixel(position, pixelposition, source, screen_width_,screen_height_)){  
                    dest.x = pixelposition.x;
                    dest.y = pixelposition.y;
                    if(!isLocked_){
                            //shuts off rotation if size is small
                            if(source.w == minBodySize_ && source.h == minBodySize_){
                                Textures::GetTextures()->Draw(index,NULL, &dest, 0.0, NULL, SDL_FLIP_NONE);
                            }else{
                                //rotation of the body
                                Vector2Elm displCenter;
                                displCenter = {imgDataX*scale_factor_, imgDataY*scale_factor_};
                                SDL_Rect zero = {0,0,0,0};
                                //Convert offset to pixel
                                PixelMath::ConvertPositionToPixel(displCenter, center, zero, dest.w, dest.h);
                                //convert position to pixel position
                                PixelMath::ConvertPositionToPixel(position, pixelposition, source, screen_width_,screen_height_);
                                Textures::GetTextures()->Draw(index,NULL, &dest, AuxMath::degrees(-angle), NULL, SDL_FLIP_NONE);
                            } 
                    }else{
                        if(thisBody->GetName() != refBody->GetName()){ 
                            //shuts off rotation if size is small
                            if(source.w == minBodySize_ && source.h == minBodySize_){
                                Textures::GetTextures()->Draw(index,NULL, &dest, 0.0, NULL, SDL_FLIP_NONE);
                            }else{
                                //rotation of the body
                                Vector2Elm displCenter;
                                displCenter = {imgDataX*scale_factor_, imgDataY*scale_factor_};
                                SDL_Rect zero = {0,0,0,0};
                                //Convert offset to pixel
                                PixelMath::ConvertPositionToPixel(displCenter, center, zero, dest.w, dest.h);
                                //convert position to pixel position
                                PixelMath::ConvertPositionToPixel(position, pixelposition, source, screen_width_,screen_height_);
                                Textures::GetTextures()->Draw(index,NULL, &dest, AuxMath::degrees(-angle), NULL, SDL_FLIP_NONE);
                            }    
                        }else{
                           Textures::GetTextures()->Draw(index,NULL, &dest, 0.0, NULL, SDL_FLIP_NONE);   
                        }
                    }
                    
                    SDL_SetRenderDrawColor( sdl_renderer_, 0, 0, 0, 0xFF );
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
                     if(scale_factor_ <= maximumScaleFactor_){
                         scale_factor_ *= 2;
                         displ_ = displ_*2;
                     }
                     break;
                case SDLK_x:
                     if(scale_factor_ >= minimumScaleFactor_){
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
                    multiplyDelta(2); //doubles number of pixels you move
                    break;
                case SDLK_m:
                    multiplyDelta(1/2); //halves number of pixels you move
                    break;
                case SDLK_l:
                    isLocked_ = !isLocked_;
                    break;    

            }
        }    
    }
}




