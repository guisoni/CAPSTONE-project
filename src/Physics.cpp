#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <memory>
#include <numeric>
class Vector2Elm
{
    public:
    //Constructor
    Vector2Elm():x_{0},y_{0}{};
    Vector2Elm(double x,double y): x_{x}, y_{y}{}
    
    //this + Vector2Elm
    Vector2Elm operator+(const Vector2Elm &b)const{
        Vector2Elm a;
        a.x_ = x_+b.x_;
        a.y_ = y_+b.y_;
        return a;
    }
    //this + Vector2Elm
    Vector2Elm operator+(const Vector2Elm &&b)const{
        Vector2Elm a;
        a.x_ = x_+b.x_;
        a.y_ = y_+b.y_;
        return a;
    }
    //this - Vector2Elm
    Vector2Elm operator-(const Vector2Elm &b)const{
        Vector2Elm a;
        a.x_ = x_-b.x_;
        a.y_ = y_-b.y_;
        return a;
    }
    //this - Vector2Elm
    Vector2Elm operator-(const Vector2Elm &&b)const{
        Vector2Elm a;
        a.x_ = x_-b.x_;
        a.y_ = y_-b.y_;
        return a;
    }
    //this times a scalar
    Vector2Elm operator*(const double &c) const {
        Vector2Elm a;
        a.x_ = x_* c;
        a.y_ = y_* c;
        return a; 
    }
    //this  times a scalar
    Vector2Elm operator*(const double &&c) const {
        Vector2Elm a;
        a.x_ = x_* c;
        a.y_ = y_* c;
        return a; 
    }
    //this divided by a scalar
    Vector2Elm operator/(const double &c) const {
        Vector2Elm a;
        if(c == 0) {throw std::runtime_error("Division by Zero\n");}
        a.x_ = x_/ c;
        a.y_ = y_/ c;
        return a;
    }
    //this divided by a scalar
    Vector2Elm operator/(const double &&c) const {
        Vector2Elm a;
        if(c == 0) {throw std::runtime_error("Division by Zero\n");}
        a.x_ = x_/ c;
        a.y_ = y_/ c;
        return a; 
    }

    //this scalar product Vector2Elm 
    Vector2Elm operator*(const Vector2Elm &b) const {
        Vector2Elm a;
        a.x_ = x_ * b.x_;
        a.y_ = y_ * b.y_;
        return a; 
    }
    //this scalar product Vector2Elm 
    Vector2Elm operator*(const Vector2Elm &&b) const {
        Vector2Elm a;
        a.x_ = x_ * b.x_;
        a.y_ = y_ * b.y_;
        return a; 
    }
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &b) const {
       return x_*b.y_-y_*b.x_;
    }
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &&b) const {
       return x_*b.y_-y_*b.x_;
    }
    
    double abs() {
        return sqrt(pow(x_,2.0)+pow(y_,2.0));
    }

    double x_;
    double y_;
};

class Body{
    public:
    Body():
         position_{0.,0.},
         velocity_{0.,0.},
         acceleration_{0.,0.},
         angular_position_{0.},
         angular_velocity_{0.},
         mass_{0.},
         mass_moment_Inertia_{0.},
         bodyName_{""},
         Perihelion_{0.},
         Aphelion_{0.}{}

    Body(Vector2Elm pos, Vector2Elm vel, Vector2Elm accel, double ang_pos, double ang_vel, double mass, double J, std::string body_name, double perihl, double aphl ) : position_{pos}, velocity_{vel}, acceleration_{accel}, angular_position_{ang_pos},angular_velocity_{ang_vel}, mass_{mass}, mass_moment_Inertia_{J}, bodyName_{body_name}, Perihelion_{perihl}, Aphelion_{aphl} {}    
    Vector2Elm GetPosition(){return position_;}
    Vector2Elm GetVelocity(){return velocity_;}
    Vector2Elm GetAcceleration(){return acceleration_;}
    double GetAngularPosition(){return angular_position_;}
    double GetAngularVelocity(){return angular_velocity_;}
    double GetMass(){return mass_;}
    double GetMomentInertia(){return mass_moment_Inertia_;}
    std::string GetName(){return bodyName_;}

    Vector2Elm GravityForcePerMass(const Body *b){
        const double GravitationalConst = 0.0000003929131713; 
        Vector2Elm deltaPosition = b->position_- position_;
        return (deltaPosition)/pow(deltaPosition.abs(), 3.0)*(GravitationalConst * b->mass_);
    }
        void UpdateAcceleration(std::vector<std::shared_ptr<Body>> *bodies){
        Vector2Elm force(0,0);
        for(auto body = bodies->begin(); body != bodies->end(); body++){
            if(bodyName_ != (**body).bodyName_){
              acceleration_ = force + GravityForcePerMass((*body).get());
            }
        }
    }
    void UpdateVelocity(const double &dt){
        velocity_ = velocity_ + acceleration_ * dt;
    }
    void UpdatePosition(const double &dt){
        position_ = position_ + velocity_ * dt;
    }
    void UpdateAngularPosition(const double &dt){
        angular_position_ += angular_velocity_ * dt;
    } 
     //aproximated initial velocity
      void VectorItitialVelocity(const Body *sun){ 
          if(bodyName_ == sun->bodyName_){return;}    
          double a = (Perihelion_ + Aphelion_)/2;
          Vector2Elm force(0,0);
          Vector2Elm accel;
          accel = force + GravityForcePerMass(sun);
          velocity_.x_= sqrt(0);
          velocity_.y_= sqrt(accel.abs()*a);
     }
      void TangentialVelocity(){
          double a = (Perihelion_ + Aphelion_)/2;
          velocity_.x_= sqrt(0);
          velocity_.y_= sqrt(acceleration_.abs()*a);
        
      }
    void PrintBody(){
                std::cout<<"The " << GetName() << "\nposition is : (";
                std::cout<< GetPosition().x_<<", "<< GetPosition().y_ <<"\nvelocity is :(";
                std::cout<< GetVelocity().x_<<", "<< GetVelocity().y_ <<"\nacceleration is: (";
                std::cout<< GetAcceleration().x_<<" "<< GetAcceleration().y_ <<")\n";
            //body->VectorItitialVelocity(solar_system[10]);
    }

    private:
    Vector2Elm position_;
    Vector2Elm velocity_;
    Vector2Elm acceleration_;
    double angular_position_;
    double angular_velocity_;
    double mass_;
    double mass_moment_Inertia_;
    std::string bodyName_;
    double Perihelion_;
    double Aphelion_; 
};

class SolarSystem{
    public:
    static SolarSystem* GetSolarSystem(){
        if(solar_system_ ==nullptr){
            solar_system_ = new SolarSystem();
            return solar_system_;
        }else{
            return solar_system_;
        }
    }
    void ImportData(){
        std::ifstream filestream("./planets.txt");
        std::string line;
        int numlines = 0;
        bool is_imported = true;
        if (filestream.is_open()){
            while (std::getline(filestream, line)){
                numlines +=1;
                if(numlines >1){
                    Vector2Elm pos, vel, accel;
                    double ang_pos, ang_vel, mass, J, perihl, aphl;
                    std::string name;
                    std::istringstream strstream(line);
                    if(strstream >> pos.x_>> pos.y_ >> vel.x_ >> vel.y_ >> accel.x_ >> accel.y_ >> ang_pos >> ang_vel >> mass >> J >> name >> perihl >> aphl){
                        std::unique_ptr<Body> b = std::make_unique<Body>(Body(pos,vel,accel,ang_pos,ang_vel,mass,J,name,perihl,aphl));
                        AddBody(std::move(b));
                        std::cout<< numlines <<"\n";
                        is_imported_ = is_imported && true;
                    }else{
                        std::cerr << "Cannot load the planets data!"<<"\n";
                        is_imported_ = false;
                    }
                }
            }
            CenterOfMass();
        }
    }

    void AddBody(std::unique_ptr<Body> body){
        bodies_.emplace_back(std::move(body));
    }
    void Update(const double dt){
        for(auto body = bodies_.begin(); body != bodies_.end(); body++){
            (**body).UpdateAcceleration(&bodies_);
            if(is_start){
            (**body).TangentialVelocity();
            (**body).UpdateVelocity(dt/2);
            is_start = false;
            }else{
            (**body).UpdateVelocity(dt);
            }
        }
        for(auto body = bodies_.begin(); body != bodies_.end(); body++){
            if((**body).GetName()!="SUN"){
                (**body).UpdatePosition(dt);
            }
        }
    }
    void PrintBody(int id){
        if(id >= bodies_.size()){
            std::cerr << "The maximum id is " << bodies_.size()-1 << "\n"; 
        }else{
        bodies_[id]->PrintBody();
        }        
    }
    void TotalMass(){
        for(auto body = bodies_.begin(); body != bodies_.end(); body++){
            totalMass_ +=(**body).GetMass();
        }
    }

    void CenterOfMass(){
         TotalMass();
         position_ = {0,0};
        for(auto body = bodies_.begin(); body != bodies_.end(); body++){
            
            position_= ((**body).GetPosition()*(**body).GetMass());
        }
        position_ = position_/totalMass_;
    }
    double GetTotalMass(){return totalMass_;}

    Vector2Elm GetPosition(){return position_;}

    bool GetIsImported(){return is_imported_;}

    private:
    SolarSystem(){}
    static SolarSystem* solar_system_;
    std::vector<std::shared_ptr<Body>> bodies_;
    bool is_start = true;
    Vector2Elm position_;
    double totalMass_= 0;;
    bool is_imported_= false;
};

#endif

SolarSystem * SolarSystem::solar_system_ = nullptr;
int main(){   
    SolarSystem::GetSolarSystem()->ImportData();
    std::cout<< "Total Mass of solar system is: " << SolarSystem::GetSolarSystem()->GetTotalMass() <<"\n";
    std::cout<< "("<<SolarSystem::GetSolarSystem()->GetPosition().x_<<", " << SolarSystem::GetSolarSystem()->GetPosition().y_<<")\n";
    if(SolarSystem::GetSolarSystem()->GetIsImported()){    
        double dt = 10;
        long long year = sqrt(4 * 3.1415*3.1415/6.67/1.989*pow(159.6,3.0)*1e8)/dt;
        year = 3600*24*366/10;
        for(long long i = 0; i <= year; i++){
            SolarSystem::GetSolarSystem()->Update(dt);
            if((i == 0 || i == year/4 || i == year/2 || i ==year*3/4 || i ==year)){
                SolarSystem::GetSolarSystem()->PrintBody(2);
            }
        }    
    }
}

     
    