
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Rupture/Math/Vec2.h"

TEST_CASE("Vec2 addition"){
    Rupture::Vec2 a(1.0f, 2.0f);
    Rupture::Vec2 b(3.0f, 4.0f);
    Rupture::Vec2 result = a + b;

    REQUIRE(result.x == Catch::Approx(4.0f));
    REQUIRE(result.y == Catch::Approx(6.0f));
}

TEST_CASE("Vec2 subtraction"){
    Rupture::Vec2 a(1.0f, 2.0f);
    Rupture::Vec2 b(3.0f, 4.0f);
    Rupture::Vec2 result = a - b;

    REQUIRE(result.x == Catch::Approx(-2.0f));
    REQUIRE(result.y == Catch::Approx(-2.0f));
}

TEST_CASE("Vec2 Scalar Multiply"){
    Rupture::Vec2 a(1.0f, 2.0f);
    float scalar = 2.0f;
    Rupture::Vec2 result = a * scalar;

    REQUIRE(result.x == Catch::Approx(2.0f));
    REQUIRE(result.y == Catch::Approx(4.0f));
}

TEST_CASE("Vec2 Scalar Divide"){
    Rupture::Vec2 a(10.0f, 2.0f);
    float scalar = 2.0f;
    Rupture::Vec2 result = a / scalar;

    REQUIRE(result.x == Catch::Approx(5.0f));
    REQUIRE(result.y == Catch::Approx(1.0f));
}

TEST_CASE("Vec2 Negation"){
    Rupture::Vec2 a(10.0f, 5.0f);
    Rupture::Vec2 result = -a;

    REQUIRE(result.x == Catch::Approx(-10.0f));
    REQUIRE(result.y == Catch::Approx(-5.0f));
}

TEST_CASE("Vec2 equality") {
    Rupture::Vec2 a(1.0f, 2.0f);
    Rupture::Vec2 b(1.0f, 2.0f);

    REQUIRE(a == b);
}

TEST_CASE("Vec2 Perpendicular") {
    Rupture::Vec2 a(1.0f, 0.0f);
    Rupture::Vec2 b(0.0f, 1.0f);

    REQUIRE(a.Dot(b) == Catch::Approx(0));
}

TEST_CASE("Vec2 Same Direction") {
    Rupture::Vec2 a(1.0f, 1.0f);
    Rupture::Vec2 b(1.0f, 1.0f);
    float result = a.Dot(b);

    REQUIRE(result > 0.0f);
}

TEST_CASE("Vec2 Length"){
    Rupture::Vec2 a(3.0f, 4.0f);

    REQUIRE(a.Length() == Catch::Approx(5));
}

TEST_CASE("Vec2 Normailze"){
    Rupture::Vec2 a(1.0f, 2.0f);
    Rupture::Vec2 result = a.Normalize();

    REQUIRE(result.Length() == Catch::Approx(1));
}

TEST_CASE("Vec2 Normalize Zero"){
    Rupture::Vec2 a(0.0f, 0.0f);
    Rupture::Vec2 result = a.Normalize();

    REQUIRE(result.Length() == Catch::Approx(0));
}

