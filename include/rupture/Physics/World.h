
#pragma once

#include <memory>
#include <vector>
#include "Rupture/Math/Vec2.h"
#include "Rupture/Physics/RigidBody.h"
#include "Rupture/Shapes/Shape.h"
#include "Rupture/Physics/CollisionManifold.h"
#include "Rupture/Physics/NarrowPhase.h"
#include "Rupture/Physics/AABB.h"

namespace Rupture{
    struct CollisionPair {
        RigidBody* bodyA;
        RigidBody* bodyB;
    };

    class World{
        World(Vec2 gravity) : gravity(gravity){}
        RigidBody& AddBody(Vec2 position, float mass, std::unique_ptr<Shape> shape);
        void RemoveBody(RigidBody& body);
        const std::vector<std::unique_ptr<RigidBody>>& GetBodies() const;
        void Step(float dt);

        private:
        void ApplyGravity();
        void IntegrateBodies(float dt);
        void BroadPhase();
        void NarrowPhase();
        void ResolveCollisions();

        std::vector<std::unique_ptr<RigidBody>> bodies;
        Vec2 gravity;
        std::vector<CollisionPair> pairs;
        std::vector<CollisionManifold> manifolds;
    };
}