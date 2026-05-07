
#include <vector>
#include <limits>

#include "Rupture/Shapes/Circle.h"
#include "Rupture/Shapes/Polygon.h"
#include "Rupture/Physics/NarrowPhase.h"

auto IsPolygonLike = [](Rupture::ShapeType t){
    return t == Rupture::ShapeType::POLYGON || t == Rupture::ShapeType::BOX;
};

Rupture::CollisionManifold Rupture::NarrowPhase::Test(RigidBody& bodyA, RigidBody& bodyB) {
    if(bodyA.shape->GetShapeType() == Rupture::ShapeType::CIRCLE 
        && bodyB.shape->GetShapeType() == Rupture::ShapeType::CIRCLE){
            return Rupture::NarrowPhase::CircleVsCircle(bodyA, bodyB); 
        }
    if(bodyA.shape->GetShapeType() == Rupture::ShapeType::CIRCLE 
        && IsPolygonLike(bodyB.shape->GetShapeType())){
            return Rupture::NarrowPhase::CircleVsPolygon(bodyA, bodyB); 
        }
    if(IsPolygonLike(bodyA.shape->GetShapeType()) 
        && bodyB.shape->GetShapeType() == Rupture::ShapeType::CIRCLE) {
            return Rupture::NarrowPhase::CircleVsPolygon(bodyB, bodyA);
        }
    if(IsPolygonLike(bodyA.shape->GetShapeType()) 
        && IsPolygonLike(bodyB.shape->GetShapeType())){
            return Rupture::NarrowPhase::PolygonVsPolygon(bodyA, bodyB); 
        }

    CollisionManifold manifold;
    manifold.hasCollision = false;
    return manifold;
}

Rupture::CollisionManifold Rupture::NarrowPhase::CircleVsCircle(RigidBody& bodyA, RigidBody& bodyB){
    Circle* circleA = static_cast<Circle*>(bodyA.shape.get());
    Circle* circleB = static_cast<Circle*>(bodyB.shape.get());
    CollisionManifold manifold;

    float distance = (bodyB.position - bodyA.position).Length();
    float radiiSum = circleA->radius + circleB->radius;
    Vec2 direction = bodyB.position - bodyA.position;

    if(distance == 0.0f){
        manifold.hasCollision = true;
        manifold.normal = Vec2(1.0f, 0.0f);
        manifold.depth = circleA->radius;
        return manifold;
    }

    if(distance >= radiiSum) {
        manifold.hasCollision = false;
        return manifold;
    }

    manifold.hasCollision = true;
    manifold.normal = direction.Normalize();
    manifold.depth = radiiSum - distance;

    return manifold;
}

Rupture::CollisionManifold Rupture::NarrowPhase::PolygonVsPolygon(RigidBody& bodyA, RigidBody& bodyB){
    Polygon* polygonA = static_cast<Polygon*>(bodyA.shape.get());
    Polygon* polygonB = static_cast<Polygon*>(bodyB.shape.get());
    std::vector<Vec2> verticesA = polygonA->GetWorldVertices(bodyA.position, bodyA.angle);
    std::vector<Vec2> verticesB = polygonB->GetWorldVertices(bodyB.position, bodyB.angle);

    float minDepth = std::numeric_limits<float>::max();
    Vec2 bestAxis = Vec2(0.0f, 0.0f);
    
    CollisionManifold manifold;

    for(int i = 0; i < verticesA.size(); i++){
        Vec2 vertexA = verticesA[i];
        Vec2 vertexB = verticesA[(i + 1) % verticesA.size()];
        Vec2 edge = vertexB - vertexA;
        Vec2 axis = Vec2(-edge.y, edge.x).Normalize();
        
        auto [minA, maxA] = ProjectPolygon(verticesA, axis);
        auto [minB, maxB] = ProjectPolygon(verticesB, axis);

        if(maxA < minB || maxB < minA){
            manifold.hasCollision = false;
            return manifold;
        }

        float depth = std::min(maxA, maxB) - std::max(minA, minB);

        if(depth < minDepth){
            minDepth = depth;
            bestAxis = axis;
        }

    }
    
    for(int i = 0; i < verticesB.size(); i++){
        Vec2 vertexA = verticesB[i];
        Vec2 vertexB = verticesB[(i + 1) % verticesB.size()];
        Vec2 edge = vertexB - vertexA;
        Vec2 axis = Vec2(-edge.y, edge.x).Normalize();
        
        auto [minA, maxA] = ProjectPolygon(verticesA, axis);
        auto [minB, maxB] = ProjectPolygon(verticesB, axis);

        if(maxA < minB || maxB < minA){
            manifold.hasCollision = false;
            return manifold;
        }

        float depth = std::min(maxA, maxB) - std::max(minA, minB);

        if(depth < minDepth){
            minDepth = depth;
            bestAxis = axis;
        }

    }

    manifold.hasCollision = true;
    manifold.normal = bestAxis;
    manifold.depth = minDepth;

    Vec2 direction = bodyB.position - bodyA.position;
    if(direction.Dot(manifold.normal) < 0.0f){
        manifold.normal = -manifold.normal;
    }

    return manifold;
}

Rupture::CollisionManifold Rupture::NarrowPhase::CircleVsPolygon(RigidBody& bodyA, RigidBody& bodyB){
    Circle* circle = static_cast<Circle*>(bodyA.shape.get());
    Polygon* polygon = static_cast<Polygon*>(bodyB.shape.get());
    std::vector<Vec2> vertices = polygon->GetWorldVertices(bodyB.position, bodyB.angle);
    
    CollisionManifold manifold;
    float minDepth = std::numeric_limits<float>::max();
    Vec2 bestAxis;

    for(int i = 0; i < vertices.size(); i++){
        Vec2 vertexA = vertices[i];
        Vec2 vertexB = vertices[(i + 1) % vertices.size()];
        Vec2 edge = vertexB - vertexA;
        Vec2 axis = Vec2(-edge.y, edge.x).Normalize();
        
        auto [minA, maxA] = ProjectCircle(bodyA.position, circle->radius, axis);
        auto [minB, maxB] = ProjectPolygon(vertices, axis);

        if(maxA < minB || maxB < minA){
            manifold.hasCollision = false;
            return manifold;
        }

        float depth = std::min(maxA, maxB) - std::max(minA, minB);

        if(depth < minDepth){
            minDepth = depth;
            bestAxis = axis;
        }

    }

    Vec2 closestVertex = FindClosestVertex(bodyA.position, vertices);
    Vec2 axis = (closestVertex - bodyA.position).Normalize();
    
    auto [minA, maxA] = ProjectCircle(bodyA.position, circle->radius, axis);
    auto [minB, maxB] = ProjectPolygon(vertices, axis);
    
    if(maxA < minB || maxB < minA){
        manifold.hasCollision = false;
        return manifold;
    }

    float depth = std::min(maxA, maxB) - std::max(minA, minB);

    if(depth < minDepth){
        minDepth = depth;
        bestAxis = axis;
    }

    manifold.hasCollision = true;
    manifold.normal = bestAxis;
    manifold.depth = minDepth;

    Vec2 direction = bodyB.position - bodyA.position;
    if(direction.Dot(manifold.normal) < 0.0f){
        manifold.normal = -manifold.normal;
    }

    return manifold;
}

std::pair<float, float> Rupture::NarrowPhase::ProjectPolygon(const std::vector<Rupture::Vec2>& vertices, const Rupture::Vec2& axis) {
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::lowest();

    for(const Rupture::Vec2& vertex : vertices){
        float projection = vertex.Dot(axis);
        if(projection < min) min = projection;
        if(projection > max) max = projection;
    }

    return std::make_pair(min, max);
}

std::pair<float, float> Rupture::NarrowPhase::ProjectCircle(const Rupture::Vec2& center, float radius, const Rupture::Vec2& axis){
    float projection = center.Dot(axis);
    float min = projection - radius;
    float max = projection + radius;

    return std::make_pair(min, max);
}

Rupture::Vec2 Rupture::NarrowPhase::FindClosestVertex(const Rupture::Vec2& point, const std::vector<Rupture::Vec2>& vertices){
    float minDistance = std::numeric_limits<float>::max();
    Rupture::Vec2 closest = vertices[0];
    
    for(const Rupture::Vec2& vertex : vertices) {
        float distance = (vertex - point).Length();
        if(distance < minDistance){
            minDistance = distance;
            closest = vertex;
        }
    }

    return closest;
}