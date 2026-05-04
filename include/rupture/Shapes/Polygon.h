
#pragma once

#include <vector>
#include "Rupture/Shapes/Shape.h"

namespace Rupture {
    class Polygon : public Shape {
        public:
        std::vector<Vec2> vertices;
        Polygon(std::vector<Vec2> vertices) : vertices(vertices) {};
        AABB GetAABB(Vec2 position, float angle) const override;
        ShapeType GetShapeType() const override;
        std::vector<Vec2> GetWorldVertices(Vec2 position, float angle) const;
    };
}