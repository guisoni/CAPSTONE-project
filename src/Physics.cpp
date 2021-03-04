#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <memory>
#include <numeric>
#include "Physics.h"
    
//this + Vector2Elm
Vector2Elm Vector2Elm::operator+(const Vector2Elm &b)const{
    Vector2Elm a;
    a.x_ = x_+b.x_;
    a.y_ = y_+b.y_;
    return a;
}
//this + Vector2Elm
Vector2Elm Vector2Elm::operator+(const Vector2Elm &&b)const{
    Vector2Elm a;
    a.x_ = x_+b.x_;
    a.y_ = y_+b.y_;
    return a;
}
//this - Vector2Elm
Vector2Elm Vector2Elm::operator-(const Vector2Elm &b)const{
    Vector2Elm a;
    a.x_ = x_-b.x_;
    a.y_ = y_-b.y_;
    return a;
}
//this - Vector2Elm
Vector2Elm Vector2Elm::operator-(const Vector2Elm &&b)const{
    Vector2Elm a;
    a.x_ = x_-b.x_;
    a.y_ = y_-b.y_;
    return a;
}

//this times a scalar
Vector2Elm Vector2Elm::operator*(const double &c) const {
    Vector2Elm a;
    a.x_ = x_* c;
    a.y_ = y_* c;
    return a; 
}

//this  times a scalar
Vector2Elm Vector2Elm::operator*(const double &&c) const {
    Vector2Elm a;
    a.x_ = x_* c;
    a.y_ = y_* c;
    return a; 
}
//this divided by a scalar
Vector2Elm Vector2Elm::operator/(const double &c) const {
    Vector2Elm a;
    if(c == 0) {throw std::runtime_error("Division by Zero\n");}
    a.x_ = x_/ c;
    a.y_ = y_/ c;
    return a;
}

//this divided by a scalar
Vector2Elm Vector2Elm::operator/(const double &&c) const {
    Vector2Elm a;
    if(c == 0) {throw std::runtime_error("Division by Zero\n");}
        a.x_ = x_/ c;
        a.y_ = y_/ c;
        return a; 
}

//this scalar product Vector2Elm 
Vector2Elm Vector2Elm::operator*(const Vector2Elm &b) const {
    Vector2Elm a;
    a.x_ = x_ * b.x_;
    a.y_ = y_ * b.y_;
    return a; 
}
//this scalar product Vector2Elm 
Vector2Elm Vector2Elm::operator*(const Vector2Elm &&b) const {
    Vector2Elm a;
    a.x_ = x_ * b.x_;
    a.y_ = y_ * b.y_;
    return a; 
}
    //this vectorial product a Vector2Elm
    double Vector2Elm::operator^(const Vector2Elm &b) const {
       return x_*b.y_-y_*b.x_;
    }
    //this vectorial product a Vector2Elm
    double Vector2Elm::operator^(const Vector2Elm &&b) const {
       return x_*b.y_-y_*b.x_;
    }
    
    double Vector2Elm::abs() const {
        return sqrt(pow(x_,2.0)+pow(y_,2.0));
    }



Vector2Elm Body::GravityForcePerMass(const Body *b){
    const double GravitationalConst = 0.0000003929131713; 
    Vector2Elm deltaPosition = b->position_- position_;
    return (deltaPosition)/pow(deltaPosition.abs(), 3.0)*(GravitationalConst * b->mass_);
}

void Body::UpdateAcceleration(std::vector<std::shared_ptr<Body>> *bodies){
    Vector2Elm force(0,0);
    for(auto body = bodies->begin(); body != bodies->end(); body++){
        if(bodyName_ != (**body).bodyName_){
          acceleration_ = force + GravityForcePerMass((*body).get());
        }
    }
}

void Body::UpdateVelocity(const double &dt){
    velocity_ = velocity_ + acceleration_ * dt;
}

void Body::UpdatePosition(const double &dt){
    position_ = position_ + velocity_ * dt;
}

void Body::UpdateAngularPosition(const double &dt){
    angular_position_ += angular_velocity_ * dt;
}

//aproximated initial velocity
void Body::VectorItitialVelocity(const Body *sun){ 
    if(bodyName_ == sun->bodyName_){return;}    
    double a = (Perihelion_ + Aphelion_)/2;
    Vector2Elm force(0,0);
    Vector2Elm accel;
    accel = force + GravityForcePerMass(sun);
    velocity_.x_= sqrt(0);
    velocity_.y_= sqrt(accel.abs()*a);
}
void Body::TangentialVelocity(){
    double a = (Perihelion_ + Aphelion_)/2;
    velocity_.x_= sqrt(0);
    velocity_.y_= sqrt(acceleration_.abs()*a); 
}

void Body::PrintBody(){
    std::cout<<"The " << GetName() << "\nposition is : (";
    std::cout<< GetPosition().x_<<", "<< GetPosition().y_ <<"\nvelocity is :(";
    std::cout<< GetVelocity().x_<<", "<< GetVelocity().y_ <<"\nacceleration is: (";
    std::cout<< GetAcceleration().x_<<" "<< GetAcceleration().y_ <<")\n";
    //body->VectorItitialVelocity(solar_system[10]);
}


SolarSystem* SolarSystem::GetSolarSystem(){
    if(solar_system_ ==nullptr){
        solar_system_ = new SolarSystem();
        return solar_system_;
    }else{
        return solar_system_;
    }
}
void SolarSystem::ImportData(){
    std::ifstream filestream("../src/planets.txt");
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

void SolarSystem::AddBody(std::unique_ptr<Body> body){
    bodies_.emplace_back(std::move(body));
}

void SolarSystem::Update(const double dt){
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

void SolarSystem::PrintBody(int id){
    if(id >= bodies_.size()){
        std::cerr << "The maximum id is " << bodies_.size()-1 << "\n"; 
    }else{
    bodies_[id]->PrintBody();
    }        
}

void SolarSystem::TotalMass(){
    for(auto body = bodies_.begin(); body != bodies_.end(); body++){
        totalMass_ +=(**body).GetMass();
    }
}

void SolarSystem::CenterOfMass(){
    TotalMass();
    position_ = {0,0};
    for(auto body = bodies_.begin(); body != bodies_.end(); body++){
            position_= ((**body).GetPosition()*(**body).GetMass());
        }
        position_ = position_/totalMass_;
    }




     
    