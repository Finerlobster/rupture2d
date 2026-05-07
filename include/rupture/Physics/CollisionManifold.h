
#pragma once

#include "Rupture/Math/Vec2.h"
#include "Rupture/Physics/RigidBody.h"

namespace Rupture
{
    struct CollisionManifold {
        bool hasCollision;
        Vec2 normal;
        float depth;
        RigidBody* bodyA;
        RigidBody* bodyB;
    };
} 
