
#pragma once

#include "Rupture/Shapes/Shape.h"

namespace Rupture {
    class Circle : public Shape {
    public:
        float radius;
        Circle(float radius) : radius(radius){};
        AABB GetAABB(Vec2 position, float angle) const override;
        ShapeType GetShapeType() const override;
    };
}