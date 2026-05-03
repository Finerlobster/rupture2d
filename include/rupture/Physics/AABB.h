
#pragma once

#include "Rupture/Math/Vec2.h"

namespace Rupture {
    class AABB {
        public:
            AABB() : min(0.0f, 0.0f), max(0.0f, 0.0f){}
            AABB(const Vec2& min, const Vec2& max) : min(min), max(max){}

            Vec2 min;
            Vec2 max;

            bool Overlaps(const AABB& other) const;
            bool Contains(const Vec2& point) const;
    };
}
