
#include "Physics.h"
#include "Core.h"
#include "Textures.h"

SolarSystem* SolarSystem::solar_system_ = nullptr;
Core* Core::core_= nullptr;
Textures* Textures::textures_ = nullptr;
int main(){   


    SolarSystem::GetSolarSystem()->ImportData();
        if(SolarSystem::GetSolarSystem()->GetIsImported()){  
            std::cout<<"Data Imported\n";
        //std::cout<< "Total Mass of solar system is: " << SolarSystem::GetSolarSystem()->GetTotalMass() <<"\n";
        //std::cout<< "("<<SolarSystem::GetSolarSystem()->GetPosition().x_<<", " << SolarSystem::GetSolarSystem()->GetPosition().y_<<")\n";
        Core::GetCore();
        Core::GetCore()->Start();
        Core::GetCore()->RunGame();
        Core::GetCore()->EndGraphics();
        Core::FreeCore();
    }
    
}

