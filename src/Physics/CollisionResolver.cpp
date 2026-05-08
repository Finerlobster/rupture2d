
#include <algorithm>
#include "Rupture/Physics/CollisionResolver.h"

void Rupture::CollisionResolver::Resolve(Rupture::CollisionManifold& manifold){
    if(!manifold.hasCollision) return;

    CorrectPositions(manifold);
    ApplyImpulse(manifold);
}

void Rupture::CollisionResolver::ApplyImpulse(Rupture::CollisionManifold& manifold){
    Vec2 relativeVelocity = manifold.bodyB->velocity - manifold.bodyA->velocity;
    float relativeVelocityAlongNormal = relativeVelocity.Dot(manifold.normal);

    if(relativeVelocityAlongNormal > 0) return;

    float e = std::min(manifold.bodyA->restitution, manifold.bodyB->restitution);
    float impulse = -(1 + e) * relativeVelocityAlongNormal;
    impulse = impulse / (manifold.bodyA->inverseMass + manifold.bodyB->inverseMass);

    manifold.bodyA->velocity = manifold.bodyA->velocity - manifold.normal * impulse * manifold.bodyA->inverseMass;
    manifold.bodyB->velocity = manifold.bodyB->velocity + manifold.normal * impulse * manifold.bodyB->inverseMass;   
}

void Rupture::CollisionResolver::CorrectPositions(Rupture::CollisionManifold& manifold){
    float totalInverseMass = manifold.bodyA->inverseMass + manifold.bodyB->inverseMass;
    if(totalInverseMass == 0.0f) return;
    manifold.bodyA->position = manifold.bodyA->position - manifold.normal * manifold.depth * (manifold.bodyA->inverseMass / totalInverseMass);
    manifold.bodyB->position = manifold.bodyB->position + manifold.normal * manifold.depth * (manifold.bodyB->inverseMass / totalInverseMass);
}