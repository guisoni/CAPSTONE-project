#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <memory>
#include <numeric>
#include <random>
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



Vector2Elm Body::GravityForcePerMass(std::shared_ptr<Body> b){
    const double GravitationalConst = 0.0000003929131713; 
    Vector2Elm deltaPosition = b->position_- position_;
    return (deltaPosition)/pow(deltaPosition.abs(), 3.0)*(GravitationalConst * b->mass_);
}

void Body::UpdateAcceleration(std::vector<std::shared_ptr<Body>> *bodies){
    acceleration_ = {0,0};
    for(auto body = bodies->begin(); body != bodies->end(); body++){
        if(bodyName_ != (**body).bodyName_){
          acceleration_ = acceleration_ + GravityForcePerMass(*body);
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


void Body::TangentialVelocity(){
    double a = (Perihelion_ + Aphelion_)/2;
    velocity_.x_= sqrt(0);
    velocity_.y_= sqrt(acceleration_.abs()*a); 
}

void Body::PrintBody(){
    std::cout<< GetPosition().x_<<", "<< GetPosition().y_ <<"  ";//\nvelocity is :(";
    std::cout<< GetVelocity().x_<<", "<< GetVelocity().y_ <<"\n";//acceleration is: (";
    //std::cout<< GetAcceleration().x_<<" "<< GetAcceleration().y_ <<")\n";
}

Vector2Elm Body::Transform(std::shared_ptr<Body> b){
    return position_ - b->position_;
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
                    vel = {0,0};
                    if(name == "MOON"){
                        pos = pos  +  (bodies_[bodies_.size()-1])->GetPosition();
                        std::cout << pos.x_ << " " << pos.y_ <<"\n";
                    }
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
        if(is_start_){
            SolarSystem::InitialConditions();
        }
    for(auto body = bodies_.begin(); body != bodies_.end(); body++){
        (**body).UpdateAcceleration(&bodies_);
    }
    for(auto body = bodies_.begin(); body != bodies_.end(); body++){
        if(is_start_){
            (**body).UpdateVelocity(dt/2);
        }else{
            (**body).UpdateVelocity(dt);
        }
        is_start_ = false;
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
        totalMass_ +=(**body).mass_;
    }
}


void SolarSystem::CenterOfMass(){
    TotalMass();
    position_ = {0,0};
    for(auto body = bodies_.begin(); body != bodies_.end(); body++){
        position_= position_+ ((**body).position_*(**body).mass_);
    }
    position_ = position_/totalMass_;
}

//initial velocity
void SolarSystem::InitialConditions(){

    {
    //bodies_[2]->position_ = {bodies_[2]->Aphelion_,0};
    double a = (bodies_[2]->Perihelion_+bodies_[2]->Aphelion_)/2;
    double f = bodies_[2]->Aphelion_ - a;
    double b = sqrt(a*a-f*f);
    bodies_[3]->position_ = {f, b};
    }
    for(int i = 0; i < bodies_.size(); i++){
        if(bodies_[i]->bodyName_ == "SUN"){
            bodies_[i]->position_ = {0,0};
        }
        else if(bodies_[i]->bodyName_ == "EARTH"){
            
            double a = (bodies_[i]->Perihelion_+bodies_[i]->Aphelion_)/2;
            double f = bodies_[i]->Aphelion_ - a;
            double b = sqrt(a*a-f*f);
            double c = (bodies_[i+1]->Perihelion_+ bodies_[i+1]->Aphelion_)/2;
            double consta, constb, constc;
            consta = -1/(a*a)+1/(b*b);
            constb = 2*b/a/a;
            constc =  pow(c/a,2)-pow(b/a,2)-1;
            double delta = pow(constb,2)-4*consta*constc;
            delta = (delta < 0)? 0 : delta;
            bodies_[i]->position_.y_ = (-constb +sqrt(delta))/(2*consta);
            delta = (1-(pow(bodies_[i]->position_.y_/b,2)));
            delta = (delta < 0)? 0 : delta;
            bodies_[i]->position_.x_ = sqrt(delta)*a+f;
            
        }else if(bodies_[i]->bodyName_ != "MOON"){
            double a = (bodies_[i]->Perihelion_+bodies_[i]->Aphelion_)/2;
            double f = bodies_[i]->Aphelion_ - a;;
            double b = sqrt(a*a-f*f);
            std::random_device rd;
            std::mt19937 eng(rd());
            std::uniform_real_distribution<> ddistr(-bodies_[i]->Perihelion_, std::nextafter(bodies_[i]->Aphelion_, std::numeric_limits<double>::max()));
            bodies_[i]->position_.x_= ddistr(eng);
            std::uniform_int_distribution<> idistr(0,1);
            int signal =(idistr(eng) == 0)?  -1 : 1;
            double ysquared = 1-(pow((bodies_[i]->position_.x_- f)/a,2.0));
            if(ysquared < 0){
                bodies_[i]->position_.y_ = signal *b;
            }else{
                bodies_[i]->position_.y_ = signal * sqrt(ysquared)*b;
            }       
        }
    }

    for(int i = 0; i < bodies_.size(); i++){
        if(bodies_[i]->bodyName_ != "SUN"){
            if(bodies_[i]->bodyName_ != "MOON"){
                double a = (bodies_[i]->Perihelion_+bodies_[i]->Aphelion_)/2;
                double f = bodies_[i]->Aphelion_ - a;
                double b = sqrt(a*a-f*f);
                double angle = atan(-(bodies_[i]->position_.x_-f)/(bodies_[i]->position_.y_)*b*b/(a*a));
                Vector2Elm force(0,0);
                Vector2Elm accel;
                accel = force + bodies_[i]->GravityForcePerMass(bodies_[10]);
                double r = (bodies_[i]->position_-bodies_[10]->position_).abs();
                if(bodies_[i]->position_.y_ >= 0){
                    bodies_[i]->velocity_.x_=  -sqrt(accel.abs()*(2*r - r*r/a))*cos(angle);
                    bodies_[i]->velocity_.y_=  -sqrt(accel.abs()*(2*r - r*r/a))*sin(angle);  
                }else{
                    bodies_[i]->velocity_.x_=   sqrt(accel.abs()*(2*r - r*r/a))*cos(angle);
                    bodies_[i]->velocity_.y_=   sqrt(accel.abs()*(2*r - r*r/a))*sin(angle);  
                }            
            }else{   
                {
                    double a = (bodies_[i]->Perihelion_+bodies_[i]->Aphelion_)/2;
                    Vector2Elm force(0,0);
                    Vector2Elm accel;
                    accel = force + bodies_[i]->GravityForcePerMass(bodies_[i-1]);
                    double r = (bodies_[i]->position_-bodies_[i-1]->position_).abs();
                    bodies_[i]->velocity_.y_= -sqrt(accel.abs()*(2*r - r*r/a));   
                }
                double a = (bodies_[i-1]->Perihelion_+bodies_[i-1]->Aphelion_)/2;
                Vector2Elm force(0,0);
                Vector2Elm accel;
                accel = force + bodies_[i]->GravityForcePerMass(bodies_[10]);
                double r = (bodies_[i-1]->position_- bodies_[10]->position_).abs(); 
                bodies_[i]->velocity_.x_-= sqrt(accel.abs()*(2*r - r*r/a));

            }          
        }
        bodies_[i]->PrintBody();
    }
}





     
    