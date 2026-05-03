
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Rupture/Physics/RigidBody.h"

const float dt = 1.0f/60.0f;

TEST_CASE("Body with no forces position should not change when integrate."){
    Rupture::Vec2 position = Rupture::Vec2(0.0f, 0.0f);
    Rupture::RigidBody rb(position, 1.0f);
    rb.Integrate(dt);

    REQUIRE(rb.position.x == Catch::Approx(0));
    REQUIRE(rb.position.y == Catch::Approx(0));
}

TEST_CASE("Apply force"){
    Rupture::Vec2 position = Rupture::Vec2(0.0f, 0.0f);
    Rupture::RigidBody rb(position, 1.0f);
    Rupture::Vec2 force = Rupture::Vec2(1.0f, 2.0f);
    rb.ApplyForce(force);
    rb.Integrate(dt);

    REQUIRE(rb.velocity.x != Catch::Approx(0.0f));
    REQUIRE(rb.velocity.y != Catch::Approx(0.0f));
}

TEST_CASE("Static Body (mass = 0) Should not move"){
    Rupture::Vec2 position = Rupture::Vec2(0.0f, 0.0f);
    Rupture::RigidBody rb(position, 0.0f);
    Rupture::Vec2 force = Rupture::Vec2(1.0f, 2.0f);
    rb.ApplyForce(force);
    rb.Integrate(dt);

    REQUIRE(rb.position.x == Catch::Approx(0.0f));
    REQUIRE(rb.position.y == Catch::Approx(0.0f));
}




