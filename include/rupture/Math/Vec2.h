#pragma once

#include <cmath>

namespace Rupture {

    class Vec2 {
    public:
        float x;
        float y;

        Vec2() : x(0.0f), y(0.0f){}
        Vec2(float x, float y) : x(x), y(y) {}

        Vec2 operator+(const Vec2& other) const {
            return Vec2(x + other.x, y + other.y);
        }

        Vec2 operator-(const Vec2& other) const {
            return Vec2(x - other.x, y - other.y);
        }

        Vec2 operator*(const float scale) const {
            return Vec2(x * scale, y * scale);
        }

        Vec2 operator/(const float scale) const {
            return Vec2(x / scale, y / scale);
        }

        //vector negation
        Vec2 operator-() const {
            return Vec2(-x, -y);
        }

        bool operator==(const Vec2& other) const {
            float epsilon = 0.0001f;
            return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon;
        }

        float Dot(const Vec2& other) const {
            return x * other.x + y * other.y;
        }

        float LengthSq() const {
            return x * x + y * y;
        }

        float Length() const {
            return sqrt(x * x + y * y);
        }

        Vec2 Normalize() const {
            float len = Length();
            if(len == 0.0f) return Vec2(0.0f, 0.0f);
            return Vec2(x / len, y / len);
        }

        Vec2 Rotate(float angle) const {
            return Vec2(
                x * cos(angle) - y * sin(angle),
                x * sin(angle) + y * cos(angle)
            );
        }
    };
}