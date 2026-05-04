
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "Rupture/Shapes/Circle.h"
#include "Rupture/Shapes/Polygon.h"
#include "Rupture/Shapes/Box.h"
#include "Rupture/Physics/AABB.h"
#include "Rupture/Math/Vec2.h"

using namespace Rupture;

TEST_CASE("Circle AABB and get shape"){
    Circle a(2.0f);
    AABB aabb = a.GetAABB(Vec2(0.0f, 0.0f), 0.0f);

    REQUIRE(aabb.min.x == Catch::Approx(-2.0f));
    REQUIRE(aabb.min.y == Catch::Approx(-2.0f));
    REQUIRE(aabb.max.x == Catch::Approx(2.0f));
    REQUIRE(aabb.max.y == Catch::Approx(2.0f));

    REQUIRE(a.GetShapeType() == ShapeType::CIRCLE);
}

TEST_CASE("Polygon AABB and get shape"){
    Polygon a({
        Vec2(-1.0f, -1.0f),
        Vec2(-1.0f, 1.0f),
        Vec2(1.0f, -1.0f),
        Vec2(1.0f, 1.0f)
    });

    AABB aabb = a.GetAABB(Vec2(0.0f, 0.0f), 0.0f);

    REQUIRE(aabb.min.x == Catch::Approx(-1.0f));
    REQUIRE(aabb.max.x == Catch::Approx(1.0f));
    REQUIRE(aabb.min.y == Catch::Approx(-1.0f));
    REQUIRE(aabb.max.y == Catch::Approx(1.0f));

    REQUIRE(a.GetShapeType() == ShapeType::POLYGON);
    
}

TEST_CASE("Box AABB and get shape"){
    Box a(2.0f, 2.0f);

    AABB aabb = a.GetAABB(Vec2(0.0f, 0.0f), 0.0f);

    REQUIRE(aabb.min.x == Catch::Approx(-2.0f));
    REQUIRE(aabb.max.x == Catch::Approx(2.0f));
    REQUIRE(aabb.min.y == Catch::Approx(-2.0f));
    REQUIRE(aabb.max.y == Catch::Approx(2.0f));

    REQUIRE(a.GetShapeType() == ShapeType::BOX);
}

