
#include <limits>
#include "Rupture/Shapes/Polygon.h"

Rupture::AABB Rupture::Polygon::GetAABB(Vec2 position, float angle) const {
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for(const Vec2& vertex : GetWorldVertices(position, angle)){
        if(vertex.x < minX) minX = vertex.x;
        if(vertex.x > maxX) maxX = vertex.x;
        if(vertex.y < minY) minY = vertex.y;
        if(vertex.y > maxY) maxY = vertex.y;
    }

    return AABB(Vec2(minX, minY), Vec2(maxX, maxY));
}

Rupture::ShapeType Rupture::Polygon::GetShapeType() const {
    return Rupture::ShapeType::POLYGON;
}

std::vector<Rupture::Vec2> Rupture::Polygon::GetWorldVertices(Rupture::Vec2 position, float angle) const{
    std::vector<Vec2> worldVertices;
    for(const Vec2& vertex : vertices){
        Vec2 worldVertex = vertex.Rotate(angle) + position;
        worldVertices.push_back(worldVertex);
    }
    return worldVertices;
}