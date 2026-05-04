
#include "Rupture/Shapes/Circle.h"

Rupture::AABB Rupture::Circle::GetAABB(Rupture::Vec2 position, float /*angle*/) const {
    return Rupture::AABB(position - Rupture::Vec2(radius, radius), position + Rupture::Vec2(radius, radius)); 
}

Rupture::ShapeType Rupture::Circle::GetShapeType() const {
    return Rupture::ShapeType::CIRCLE;
}

