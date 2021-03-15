#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <memory>
#include <numeric>
#include <random> 

class SolarSystem{
    public:
    static SolarSystem* GetSolarSystem();

    void ImportData();
    
    void AddBody(std::unique_ptr<Body> body);

    void Update(const double &dt);

    void PrintBody(const int &id) const ;

    void TotalMass();

    void CenterOfMass();

    double GetTotalMass(){return totalMass_;}

    Vector2Elm GetPosition(){return position_;}

    bool GetIsImported(){return is_imported_;}

    int GetNumberOfBodies(){return bodies_.size();}

    std::shared_ptr<Body> GetBody(int id){return bodies_.at(id);}

    std::string BodyName(int id){return bodies_.at(id)->GetName();}   

    void InitialConditions();
   
    private:
    SolarSystem(){}
    static SolarSystem* solar_system_;
    std::vector<std::shared_ptr<Body>> bodies_;
    bool is_start_ = true;
    Vector2Elm position_;
    double totalMass_= 0;;
    bool is_imported_= true;
};

#endif