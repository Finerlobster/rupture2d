
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>
#include <vector>
#include "Rupture/Physics/RigidBody.h"
#include "Rupture/Shapes/Circle.h"
#include "Rupture/Shapes/Polygon.h"
#include "Rupture/Physics/NarrowPhase.h"

using namespace Rupture;

TEST_CASE("Circle vs Circle"){
    RigidBody a(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<Circle>(2.0f));
    RigidBody b(Vec2(3.0f, 0.0f), 1.0f, std::make_unique<Circle>(2.0f));
    CollisionManifold manifold;

    manifold = NarrowPhase::Test(a, b);

    REQUIRE(manifold.hasCollision);

    REQUIRE(manifold.depth == Catch::Approx(1.0f));
    REQUIRE(manifold.normal.x == Catch::Approx(1.0f)); // points right
    REQUIRE(manifold.normal.y == Catch::Approx(0.0f));
}

TEST_CASE("Circle vs Circle no collision"){
    RigidBody a(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<Circle>(1.0f));
    RigidBody b(Vec2(10.0f, 0.0f), 1.0f, std::make_unique<Circle>(1.0f));
    CollisionManifold manifold = NarrowPhase::Test(a, b);
    REQUIRE_FALSE(manifold.hasCollision);
}


TEST_CASE("Circle vs Polygon"){
    RigidBody a(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<Circle>(2.0f));
    std::vector<Vec2> vertices = {
        Vec2(0.0f, 0.0f),
        Vec2(0.0f, 1.0f),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f)
    };
    RigidBody b(Vec2(2.0f, 0.0f), 1.0f, std::make_unique<Polygon>(vertices));
    CollisionManifold manifold;

    manifold = NarrowPhase::Test(a, b);

    REQUIRE(manifold.hasCollision);
}

TEST_CASE("Polygon vs Polygon"){
    std::vector<Vec2> verticesA = {
        Vec2(0.0f, 0.0f),
        Vec2(0.0f, 1.0f),
        Vec2(1.0f, 0.0f),
        Vec2(1.0f, 1.0f)
    };
    std::vector<Vec2> verticesB = {
        Vec2(0.5f, 0.5f),
        Vec2(0.5f, 1.5f),
        Vec2(1.5f, 0.5f),
        Vec2(1.5f, 1.5f)
    };
    RigidBody a(Vec2(2.0f, 0.0f), 1.0f, std::make_unique<Polygon>(verticesA));
    RigidBody b(Vec2(2.0f, 0.0f), 1.0f, std::make_unique<Polygon>(verticesB));

    CollisionManifold manifold;
    manifold = NarrowPhase::Test(a, b);

    REQUIRE(manifold.hasCollision);

}
