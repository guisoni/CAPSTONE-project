#include "Physics.h"
#include "SolarSystem.h"

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
    
double Vector2Elm::abs() const {
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


Vector2Elm Body::GravityForcePerMass(const std::shared_ptr<Body> &b) const{
    const double GravitationalConst = 0.0000003929131713; //= GM/r3
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
    if(angular_position_ >= 2*AuxMath::PI){
      angular_position_-=2*AuxMath::PI;
    }
    if(AuxMath::degrees(angular_position_) < 0){
      angular_position_+=2*AuxMath::PI;
    }
}


void Body::PrintBody(){
    std::cout<<"Body name: " << GetName() <<"\n";
    std::cout<<"Position: " << GetPosition().x_<<", "<< GetPosition().y_ <<"  ";\
    std::cout<<"Velocity: "  << GetVelocity().x_<<", "<< GetVelocity().y_ <<"\n";
    std::cout<<"Acceleration " << GetAcceleration().x_ <<" "<< GetAcceleration().y_ <<")\n";
}


