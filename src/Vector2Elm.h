#ifndef VECTOR2ELM_H
#define VECTOR2ELM_H

#include <cmath>
#include <stdexcept>

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
    double operator*(const Vector2Elm &b) const ;
    
    //this scalar product Vector2Elm 
    double operator*(const Vector2Elm &&b) const ;
    
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &b) const ;
    
    //this vectorial product a Vector2Elm
    double operator^(const Vector2Elm &&b) const ;
    
    double Abs() const;
    
    Vector2Elm Transform(const Vector2Elm &b);
    
    Vector2Elm RotationTransform(const double &angle);
    
    double x_;
    double y_;
};
#endif