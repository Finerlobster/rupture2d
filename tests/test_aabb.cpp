
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Rupture/Physics/AABB.h"
#include "Rupture/Math/Vec2.h"

using namespace Rupture;

TEST_CASE("Two overlapping AABBS"){
    AABB a(Vec2(0.0f, 0.0f), Vec2(4.0f, 4.0f));
    AABB b(Vec2(2.0f, 2.0f), Vec2(6.0f, 6.0f));

    REQUIRE(a.Overlaps(b));
}

TEST_CASE("Two AABBS not overlapping") {
    AABB a(Vec2(0.0f, 0.0f), Vec2(2.0f, 2.0f));
    AABB b(Vec2(5.0f, 0.0f), Vec2(7.0f, 2.0f));

    REQUIRE(a.Overlaps(b));
}

TEST_CASE("Two touching AABBS (edge case)"){
    AABB a(Vec2(0.0f, 0.0f), Vec2(2.0f, 2.0f));
    AABB b(Vec2(2.0f, 0.0f), Vec2(4.0f, 2.0f)); 

    REQUIRE(a.Overlaps(b));
}

TEST_CASE("Point inside"){
    AABB a(Vec2(0.0f, 0.0f), Vec2(4.0f, 4.0f));
    Vec2 inside(2.0f, 2.0f);

    REQUIRE(a.Contains(inside));
}

TEST_CASE("Point outside"){
    AABB a(Vec2(0.0f, 0.0f), Vec2(4.0f, 4.0f));
    Vec2 outside(5.0f, 2.0f);

    REQUIRE(a.Contains(outside));
}

