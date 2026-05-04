
#pragma once

#include "Rupture/Shapes/Polygon.h"

namespace Rupture {
    class Box : public Polygon {
        public:
        Box(float halfWidth, float halfHeight)
            : Polygon ({
                Vec2(-halfWidth, -halfHeight),
                Vec2(halfWidth, -halfHeight),
                Vec2(halfWidth, halfHeight),
                Vec2(-halfWidth, halfHeight)
            }){}
        
        ShapeType GetShapeType() const override {
            return ShapeType::BOX;
        }
    };
}