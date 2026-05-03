
#include "Rupture/Physics/AABB.h"

bool Rupture::AABB::Overlaps(const Rupture::AABB& other) const {
    return max.x > other.min.x && min.x < other.max.x &&
        max.y > other.min.y && min.y < other.max.y;
}

bool Rupture::AABB::Contains(const Rupture::Vec2& point) const {
    return point.x > min.x && point.x < max.x &&
        point.y > min.y && point.y < max.y;
}

