#include "Vector2Elm.h"


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
double Vector2Elm::operator*(const Vector2Elm &b) const {
    Vector2Elm a;
    a.x_ = x_ * b.x_;
    a.y_ = y_ * b.y_;
    return a.x_ + a.y_; 
}
//this scalar product Vector2Elm 
double Vector2Elm::operator*(const Vector2Elm &&b) const {
    Vector2Elm a;
    a.x_ = x_ * b.x_;
    a.y_ = y_ * b.y_;
    return a.x_ + a.y_; 
}
//this vectorial product a Vector2Elm
double Vector2Elm::operator^(const Vector2Elm &b) const {
   return x_*b.y_-y_*b.x_;
}
//this vectorial product a Vector2Elm
double Vector2Elm::operator^(const Vector2Elm &&b) const {
   return x_*b.y_-y_*b.x_;
}
    
double Vector2Elm::Abs() const {
    return sqrt(pow(x_,2.0)+pow(y_,2.0));
}

Vector2Elm Vector2Elm::Transform(const Vector2Elm &b){
    return *this - b;
}

Vector2Elm Vector2Elm::RotationTransform(const double &angle)
{
 Vector2Elm transformed_position;
 transformed_position.x_ = x_ * cos(angle) + y_*sin(angle);
 transformed_position.y_ = -x_ * sin(angle) +y_*cos(angle);
 return transformed_position;
}
