#ifndef PHYSICS_H
#define PHYSICS_H

#include <iostream>
#include <cmath>
#include <vector>
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

    static double abs(Vector2Elm &b) {
        return sqrt(pow(b.x_,2.0)+pow(b.y_,2.0));
    }

    double x_;
    double y_;
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
    double j = Vector2Elm::abs(i);
    std::cout <<"("<< a.x_ <<","<<a.y_<<") * "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< d.x_ <<","<<d.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") * "<< c <<" is "<<"("<< e.x_ <<","<<e.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") # "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<< f<<"\n";;
    std::cout <<"("<< a.x_ <<","<<a.y_<<") + "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< g.x_ <<","<<g.y_<<") \n";
    std::cout <<"("<< a.x_ <<","<<a.y_<<") - "<<"("<< b.x_ <<","<<b.y_<<")"<<" is "<<"("<< h.x_ <<","<<h.y_<<") \n";
    std::cout <<"("<< i.x_ <<","<<i.y_<<")\n";
    std::cout << j << "\n";
}