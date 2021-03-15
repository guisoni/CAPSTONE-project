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



class ImgPosScale{
    public:
        ImgPosScale():x_{0},y_{0}, scaleWidth_{0},scaleHeight_{0}{}
        ImgPosScale(double x, double y, double width, double height):x_{x},y_{y}, scaleWidth_{width},scaleHeight_{height}{}
        double X(){return x_;}
        double Y(){return y_;}
        double ScaleWidth(){return scaleWidth_;}
        double ScaleHeight(){return scaleHeight_;}

    private:
    double x_;
    double y_;
    double scaleWidth_;
    double scaleHeight_;
};

namespace AuxMath{
    const double PI = 3.14159265359;
    template <typename T>
        T radians(T angle){
            angle*=PI/180.0;
            return angle;
        }
    template <typename T>
    T degrees(T angle){
        angle*=180.0/PI;
        return angle;
    }

    template <typename T>
    T abs(T value){
        return ((value >= 0) ? value :-value); 
    }
    template <typename T>
    T sign(T value){
        if(value !=0){
            return value / abs(value);
        }
        return 1; 
    }

}

class Vector2Elm
{
    public:
    //Constructor
    Vector2Elm():x_{0},y_{0}{}
    Vector2Elm(double x,double y): x_{x}, y_{y}{}
    
    //this + Vector2Elm
    Vector2Elm operator+(const Vector2Elm &b) const;

    //this + Vector2Elm
    Vector2Elm operator+(const Vector2Elm &&b) const;

    //this - Vector2Elm
    Vector2Elm operator-(const Vector2Elm &b) const;
    
    //this - Vector2Elm
    Vector2Elm operator-(const Vector2Elm &&b) const;
    
    //this times a scalar
    Vector2Elm operator*(const double &c) const;
    
    //this  times a scalar
    Vector2Elm operator*(const double &&c) const ;

    //this divided by a scalar
    Vector2Elm operator/(const double &c) const ;

    //this divided by a scalar
    Vector2Elm operator/(const double &&c) const ;

    //this scalar product Vector2Elm 
    Vector2Elm operator*(const Vector2Elm &b) const ;
    
    //this scalar product Vector2Elm 
    Vector2Elm operator*(const Vector2Elm &&b) const ;
    
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &b) const ;
    
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &&b) const ;
    
    double abs() const;
Vector2Elm Transform(const Vector2Elm &b);
Vector2Elm RotationTransform(const double &angle);

    void LogarithmScale(){
        double r = this->abs();
        double logr = 0; 
        if(r!= 0){
          logr = log(AuxMath::abs<double>(r) + 1);
          x_ *=  logr/r;
          y_ *=  logr/r;
        }


    }
    
    double x_;
    double y_;
};


class Body{
    public:
    Body():
         position_{0.,0.}, velocity_{0.,0.}, acceleration_{0.,0.},
         angular_position_{0.}, angular_velocity_{0.},  mass_{0.},
         mass_moment_Inertia_{0.}, bodyName_{""}, Perihelion_{0.},
         Aphelion_{0.}, diameter_{0.},image_pos_scale_{}{
            
         }
    Body(double ang_vel, double mass, double J,
        std::string body_name, double perihl, double aphl,
        double diam, ImgPosScale imgData) : position_{0, 0}, velocity_{0, 0}, 
        acceleration_{0,0}, angular_position_{0},
        angular_velocity_{ang_vel}, mass_{mass}, 
        mass_moment_Inertia_{J}, bodyName_{body_name}, 
        Perihelion_{perihl}, Aphelion_{aphl},diameter_{diam} {
            image_pos_scale_ = imgData;
            
    }
        
    Vector2Elm GetPosition(){return position_;}
    Vector2Elm GetVelocity(){return velocity_;}
    Vector2Elm GetAcceleration(){return acceleration_;}
    double GetAngularPosition(){return angular_position_;}
    double GetAngularVelocity(){return angular_velocity_;}
    double GetMass(){return mass_;}
    double GetMomentInertia(){return mass_moment_Inertia_;}
    std::string GetName(){return bodyName_;}
    double GetDiameter(){return diameter_;}
    ImgPosScale GetImgData(){return this->image_pos_scale_;};

    Vector2Elm GravityForcePerMass(std::shared_ptr<Body> b);

    void UpdateAcceleration(std::vector<std::shared_ptr<Body>> *bodies);

    void UpdateVelocity(const double &dt);

    void UpdatePosition(const double &dt);
 
    void UpdateAngularPosition(const double &dt);

     //aproximated initial velocity
    void InitialVelocity(std::shared_ptr <Body> );

    void TangentialVelocity();

    void PrintBody();

    Vector2Elm Transform(std::shared_ptr<Body> b);

    Vector2Elm RotationTransform(std::shared_ptr<Body> b, double angle);

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
    double diameter_; 
    ImgPosScale image_pos_scale_;
    friend class SolarSystem;
};

class SolarSystem{
    public:
    static SolarSystem* GetSolarSystem();

    void ImportData();
    
    void AddBody(std::unique_ptr<Body> body);

    void Update(const double dt);

    void PrintBody(int id);

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
    bool is_imported_= false;
};

#endif


     
    