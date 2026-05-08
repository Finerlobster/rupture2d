
#include "Rupture/Physics/World.h"
#include "Rupture/Physics/CollisionResolver.h"

#include <algorithm>

Rupture::RigidBody& Rupture::World::AddBody(Rupture::Vec2 position, float mass, std::unique_ptr<Rupture::Shape> shape){
    auto body = std::make_unique<RigidBody>(position, mass, std::move(shape));
    bodies.push_back(std::move(body));
    return *bodies.back();
}

void Rupture::World::RemoveBody(Rupture::RigidBody& body){
    bodies.erase(
        std::remove_if(bodies.begin(), bodies.end(), 
            [&body](const std::unique_ptr<RigidBody>& b){
                return b.get() == &body;
            }),
        bodies.end()
    );
}

const std::vector<std::unique_ptr<Rupture::RigidBody>>& Rupture::World::GetBodies() const {
    return bodies;
}

void Rupture::World::Step(float dt){
    ApplyGravity();
    IntegrateBodies(dt);
    BroadPhaseStep();
    NarrowPhaseStep();
    ResolveCollisions();
}

void Rupture::World::ApplyGravity(){
    for(auto& body : bodies){
        if(body->inverseMass == 0.0f) continue;
        body->ApplyForce(gravity * body->mass);
    }
}

void Rupture::World::IntegrateBodies(float dt){
    for(auto& body : bodies){
        body->Integrate(dt);
    }
}

void Rupture::World::BroadPhaseStep(){
    pairs.clear();
    for(int i = 0; i < bodies.size(); i++){
        for(int j = i+1; j < bodies.size(); j++){
            auto& bodyA = bodies[i];
            auto& bodyB = bodies[j];

            if(bodyA->mass == 0.0f && bodyB->mass == 0.0f) continue;
            if(bodyA->shape->GetAABB(bodyA->position, bodyA->angle).Overlaps(bodyB->shape->GetAABB(bodyB->position, bodyB->angle))){
                CollisionPair pair;
                pair.bodyA = bodyA.get();
                pair.bodyB = bodyB.get();
                pairs.push_back(pair);
            }
        }
    }
}

void Rupture::World::NarrowPhaseStep(){
    manifolds.clear();
    for(auto& pair : pairs){
        CollisionManifold manifold = Rupture::NarrowPhase::Test(*pair.bodyA, *pair.bodyB);
        if(manifold.hasCollision){
            manifolds.push_back(manifold);
        }
    }
}

void Rupture::World::ResolveCollisions(){
    for(auto& manifold : manifolds) {
        CollisionResolver::Resolve(manifold);
    }
}


