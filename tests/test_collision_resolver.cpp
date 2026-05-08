
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>
#include <vector>
#include "Rupture/Physics/RigidBody.h"
#include "Rupture/Shapes/Circle.h"
#include "Rupture/Shapes/Polygon.h"
#include "Rupture/Physics/NarrowPhase.h"
#include "Rupture/Physics/CollisionResolver.h"

using namespace Rupture;

TEST_CASE("Circle vs Circle"){
    RigidBody a(Vec2(0.0f, 0.0f), 1.0f, std::make_unique<Circle>(2.0f));
    RigidBody b(Vec2(3.0f, 0.0f), 1.0f, std::make_unique<Circle>(2.0f));
    CollisionManifold manifold;

    manifold = NarrowPhase::Test(a, b);

    REQUIRE(manifold.hasCollision);
    REQUIRE_FALSE(a.velocity.x == Catch::Approx(0));
    REQUIRE_FALSE(a.velocity.y == Catch::Approx(0));
}