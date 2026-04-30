
#include "rupture/Physics/RigidBody.h"

void Rupture::RigidBody::Integrate(float dt){
    Vec2 acceleration;
    acceleration = force * inverseMass;
    velocity = velocity + acceleration * dt;
    position = position + velocity * dt;
    force = Vec2(0.0f, 0.0f);
    
    float angularAcceleration = torque * inverseMass;
    angularVelocity = angularVelocity + angularAcceleration * dt;
    angle = angle + angularVelocity * dt;
    torque = 0.0f;
}

void Rupture::RigidBody::ApplyForce(Vec2 force){
    this->force = this->force + force;
}

