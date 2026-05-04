
#pragma once

#include "Rupture/Physics/AABB.h"

namespace Rupture {
    enum class ShapeType {
        CIRCLE,
        POLYGON,
        BOX
    };

    class Shape {
        public:       
        virtual AABB GetAABB(Vec2 position, float angle) const = 0;
        virtual ShapeType GetShapeType() const = 0;
        virtual ~Shape() = default;
    };
}