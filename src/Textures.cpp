
//#include <iostream>
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"
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
void Textures::TextureFromImageLoad(std::string filename){
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
void Textures::EndTexture(){
    if(texture_ != nullptr){
        SDL_DestroyTexture( texture_ );
        texture_ = nullptr;
        std::cout << "Texture destroyed.\n";

    }
}


