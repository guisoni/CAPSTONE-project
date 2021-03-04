
#include "Physics.h"
#include "Core.h"
#include "Textures.h"

SolarSystem* SolarSystem::solar_system_ = nullptr;
Core* Core::core_= nullptr;
Textures* Textures::textures_ = nullptr;
int main(){   


    SolarSystem::GetSolarSystem()->ImportData();
    
    if(SolarSystem::GetSolarSystem()->GetIsImported()){   
        std::cout<< "Total Mass of solar system is: " << SolarSystem::GetSolarSystem()->GetTotalMass() <<"\n";
        std::cout<< "("<<SolarSystem::GetSolarSystem()->GetPosition().x_<<", " << SolarSystem::GetSolarSystem()->GetPosition().y_<<")\n";
        Core::GetCore();
        Core::GetCore()->Start(); 
        double dt = 10;
        while(Core::GetCore()->GetStatus()){
            Core::GetCore()->ClearRenderer();
            Textures::GetTextures()->TextureFromImageLoad("../image/EARTH1.png");
            Core::GetCore()->Renderer();
            Core::GetCore()->EventHandler();
            
            SolarSystem::GetSolarSystem()->Update(dt);
            SolarSystem::GetSolarSystem()->PrintBody(2);
        }
        Textures::GetTextures()->EndTexture();
        Core::GetCore()->EndGraphics();
        Core::FreeCore();
    }
    
}

