#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

struct vec2 {
    double x, y;

    vec2 operator+(vec2 b) const { return {x + b.x, y + b.y}; }

    vec2& operator+=(vec2 b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    vec2 operator-(vec2 b) const { return {x - b.x, y - b.y}; }

    vec2& operator-=(vec2 b) {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    vec2 operator-() const { return {-x, -y}; }

    vec2 operator*(double scalar) const { return {x * scalar, y * scalar}; }

    vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vec2 operator/(double scalar) const { return {x / scalar, y / scalar}; }

    vec2& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    double size() const { return sqrt(x * x + y * y); }

    friend std::ostream& operator<<(std::ostream& os, vec2 vector) {
        return os << '(' << vector.x << ',' << vector.y << ')';
    }
};
