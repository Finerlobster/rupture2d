
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Rupture/Physics/World.h"
#include "Rupture/Shapes/Circle.h"

using namespace Rupture;

TEST_CASE("Add/Remove bodies"){
    World world(Vec2(0.0f, 9.8f));
    RigidBody& circle = world.AddBody(
        Vec2(0.0f, 0.0f),
        1.0f,
        std::make_unique<Circle>(2.0f)
    ); 

    REQUIRE(world.GetBodies().size() == 1);

    world.RemoveBody(circle);

    REQUIRE(world.GetBodies().size() == 0);

}
