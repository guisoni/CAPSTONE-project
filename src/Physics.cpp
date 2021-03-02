#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
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
         bodyName_{"earth"},
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
        const double GravitationalConst = 6.67*1.989*10/152.1/152.1/152.1e9; 
        //6.67e-11*1.989e30/152.1e9/152.1e9;
        Vector2Elm deltaPosition = b->position_- position_;
        return (deltaPosition)/pow(deltaPosition.abs(), 3.0)*(GravitationalConst * b->mass_);
    }
        void UpdateAcceleration(std::vector<Body*> bodies){
        Vector2Elm force(0,0);
        for(Body *body : bodies){
            if(this != body){
              acceleration_ = force + GravityForcePerMass(body);
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
      double a = (Perihelion_ + Aphelion_)/2;
      Vector2Elm force(0,0);
      Vector2Elm accel;
      accel = force + GravityForcePerMass(sun);
      velocity_.x_= sqrt(0);
      velocity_.y_= sqrt(accel.abs()*a);
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

#endif

int main(){
    Vector2Elm a(1,5);
    Vector2Elm b(2,2);
    double c = 10;
    Vector2Elm d = a*b;
    Vector2Elm e;
    e = a*c;
    double f = a^b;
    Vector2Elm g = a+b;
    Vector2Elm h= a-b;
    Vector2Elm i{2,2};
    i = {3, 3};
    double j = i.abs();
    std::cout <<"("<< a.x_ <<","<<a.y_<<") * "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< d.x_ <<","<<d.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") * "<< c <<" is "<<"("<< e.x_ <<","<<e.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") # "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<< f<<"\n";;
    std::cout <<"("<< a.x_ <<","<<a.y_<<") + "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< g.x_ <<","<<g.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") - "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< h.x_ <<","<<h.y_<<") \n";
    std::cout <<"("<< i.x_ <<","<<i.y_<<")\n";
    std::cout << j << "\n";
    
    //Body earth;
    //Body earth({152.1e9,0},{0,100000},{0,0},0.,0., 5.97e24,0.,"Earth", 152.1e9 , 152.1e9); //147.1e9
    Body earth({1,0},{0,0},{0,0},0.,0., 5.97e24,0.,"Earth", 1 , 1); //147.1e9
    //Body sun({0,0},{0,0},{0,0},0.,0.,1.989e30,0.,"Sun",0.,0.);
    Body sun({0,0},{0,0},{0,0},0.,0.,1,0.,"Sun",0.,0.);
    std::vector<Body*> solar_system;
    solar_system.push_back(&earth);
    solar_system.push_back(&sun);
    earth.VectorItitialVelocity(&sun);
    double dt = 1;
    long long year = sqrt(4 * 3.1415*3.1415/6.67/1.989*pow(152.1,3.0))*1e4/dt;
    std::cout <<"year : " <<year<<"\n";
    for(long long i = 0; i <= year; i++){
        earth.UpdateAcceleration(solar_system);
        //sun.UpdateAcceleration(solar_system);
        if(i==0){
        earth.UpdateVelocity(dt/2);
        //sun.UpdateVelocity(dt/2);
        }else{
        earth.UpdateVelocity(dt);

        }
        earth.UpdatePosition(dt);
        sun.UpdatePosition(dt);
        if(i == 0 || i == year/4 || i == year/2 || i ==year*3/4 || i ==year  ){
        std::cout<<std::setprecision(5)<<"pos: (" << earth.GetPosition().x_<< ", " <<earth.GetPosition().y_<<", "<<earth.GetPosition().abs()<<")"
        << " vel :("<< earth.GetVelocity().x_<< ", " <<earth.GetVelocity().y_<<", "<<earth.GetVelocity().abs()<<")"
        << " accel :("<< earth.GetAcceleration().x_<< ", " <<earth.GetAcceleration().y_<<", "<<earth.GetAcceleration().abs()<<")\n";
        }
        
    }
    
}