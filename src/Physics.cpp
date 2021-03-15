#include "Physics.h"

Vector2Elm Body::GravityForcePerMass(const std::shared_ptr<Body> &b) const{
    const double GravitationalConst = 0.0000003929131713; //= GM/r3
    Vector2Elm deltaPosition = b->position_- position_;
    return (deltaPosition)/pow(deltaPosition.Abs(), 3.0)*(GravitationalConst * b->mass_);
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


