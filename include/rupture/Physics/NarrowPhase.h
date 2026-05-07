
#pragma once

#include <utility>
#include "Rupture/Physics/CollisionManifold.h"

namespace Rupture {
    class NarrowPhase {
        public:
        static CollisionManifold Test(RigidBody& bodyA, RigidBody& bodyB);

        private:
        static CollisionManifold CircleVsCircle(RigidBody& bodyA, RigidBody& bodyB);
        static CollisionManifold CircleVsPolygon(RigidBody& bodyA, RigidBody& bodyB);
        static CollisionManifold PolygonVsPolygon(RigidBody& bodyA, RigidBody& bodyB);
        static std::pair<float, float> ProjectPolygon(const std::vector<Rupture::Vec2>& vertices, const Rupture::Vec2& axis);
        static std::pair<float, float> ProjectCircle(const Rupture::Vec2& center, float radius, const Rupture::Vec2& axis);
        static Vec2 FindClosestVertex(const Rupture::Vec2& point, const std::vector<Rupture::Vec2>& vertices);
    };
}