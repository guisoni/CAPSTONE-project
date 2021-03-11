
//#include <iostream>
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
#include <vector>
#include "Textures.h"
#include "Core.h"


Textures *Textures::GetTextures(){
    if(textures_ == nullptr){
        textures_= new Textures(); 
        std::cout<<"Textures Started\n"; 
        return textures_;
    }
    return textures_;
}        
void Textures::FreeTextures(){
    std::cout<<"Textures Ended\n";
    delete textures_;
}

void Textures::AddTexture(){
        texture_.emplace_back(nullptr);
}

void Textures::AddScaleFactor(const int &refmeasure, const double &Diam){
        scale_texture_.push_back(Diam/refmeasure);
}

void Textures::TextureFromImageLoad(int index, std::string filename){
	//Update screen 
    if(texture_.at(index) != nullptr){
        SDL_DestroyTexture( texture_.at(index) );
    texture_.at(index) = nullptr;
    }
	//Load PNG image
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str() );
	if( loadedSurface == NULL )
	{
		std::cerr<< "Image " << filename.c_str() << " not loaded! SDL_image Error: "<< IMG_GetError()<<"\n";
        success_ = false;
	}else{
        //Set a color to be transparent
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );//119, 236, 255

        //Create texture from surface pixels
        texture_.at(index) = SDL_CreateTextureFromSurface( Core::GetCore()->GetRenderer(), loadedSurface );
	    if( texture_.at(index) == nullptr )
	    {
            std::cerr<< "Texture from Image " << filename.c_str() << " not created! SDL_image Error: "<< IMG_GetError()<<"\n";
            success_ = false;
	    }

    }
	//Delete loaded surface
	SDL_FreeSurface( loadedSurface );
    //Clear screen
}

void Textures::Draw(int index, SDL_Rect *source,SDL_Rect *dest,double angle,SDL_Point *center, SDL_RendererFlip flip){
            //Render texture to screen
		SDL_RenderCopyEx( Core::GetCore()->GetRenderer(), texture_.at(index), source, dest, angle, center, flip);
        
}

void Textures::EndTexture(int index){
    if(texture_.at(index) != nullptr){
        SDL_DestroyTexture( texture_.at(index) );
        texture_.at(index) = nullptr;
        std::cout << "Texture destroyed.\n";

    }
}

int Textures::GetTextureSize(int id, SDL_Rect &textRect){
    Uint32 format;
    int access;
    int testing;
    testing = SDL_QueryTexture(texture_[id],&format, &access, &textRect.w, &textRect.h);
    return testing; 
}




