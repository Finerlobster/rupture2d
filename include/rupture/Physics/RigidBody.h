#pragma once

#include "rupture/Math/Vec2.h"

namespace Rupture {
    class RigidBody {
        public:
        
        RigidBody(Vec2 position, float mass)
            : position(position)
            , velocity(0.0f, 0.0f)
            , force(0.0f, 0.0f)
            , mass(mass)
            , inverseMass(mass > 0 ? 1.0f / mass : 0.0f)
            , angle(0.0f)
            , angularVelocity(0.0f)
            , torque(0.0f)
            , restitution(0.5f)
            , friction(0.3f)
            {}

        Vec2 position;
        Vec2 velocity;
        Vec2 force;
        float mass;
        float inverseMass;
        float angle;
        float angularVelocity;
        float torque;
        float restitution;
        float friction;

        void Integrate(float dt);
        void ApplyForce(Vec2 force);
    
    };
}