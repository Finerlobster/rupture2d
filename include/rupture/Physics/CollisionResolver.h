
#pragma once

#include "Rupture/Physics/CollisionManifold.h"

namespace Rupture {
    class CollisionResolver {
        public:
        static void Resolve(CollisionManifold& manifold);

        private:
        static void ApplyImpulse(CollisionManifold& manifold);
        static void CorrectPositions(CollisionManifold& manifold);
    };
}