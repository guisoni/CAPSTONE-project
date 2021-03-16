#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <cmath>
#include <vector>
#include <exception>
#include <iomanip>
#include <fstream>
#include <memory>
#include <numeric>
#include "Vector2Elm.h"

class ImgPosScale{
    public:
        ImgPosScale():x_{0},y_{0}, scaleWidth_{0},scaleHeight_{0}{}
        ImgPosScale(const double &x, const double &y, const double &width, const double &height):x_{x},y_{y}, scaleWidth_{width},scaleHeight_{height}{}
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
    double GetPerihelion(){return Perihelion_;}
    double GetAphelion(){return Aphelion_;}
    double GetDiameter(){return diameter_;}
    ImgPosScale GetImgData(){return this->image_pos_scale_;};

    Vector2Elm GravityForcePerMass(const std::shared_ptr<Body> &b) const;

    void UpdateAcceleration(std::vector<std::shared_ptr<Body>> *bodies);

    void UpdateVelocity(const double &dt);

    void UpdatePosition(const double &dt);
 
    void UpdateAngularPosition(const double &dt);

    void PrintBody();


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

#endif


     
    