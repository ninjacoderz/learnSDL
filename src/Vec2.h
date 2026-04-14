//
// Created by Binh Nguyen Thanh on 26/3/26.
//

#ifndef _VECTOR2_H
#define _VECTOR2_H

#pragma once
#include <iostream>
#include <cmath>

struct Vec2 {
    float x;
    float y;

    float GetLength() const {
        return std::sqrt(x * x + y * y);
    }

    float GetDistance(const Vec2& Other) const {
        return (*this - Other).GetLength();
    }

    Vec2 Normalize() const {
        float Len = GetLength();
        if (Len == 0) return {0, 0};
        return *this / Len;
    }

    Vec2 operator*(float Multiplier) const {
        return Vec2{x * Multiplier, y * Multiplier};
    }

    Vec2 operator/(float Divisor) const {
        if (Divisor == 0.0f) { return Vec2{0, 0}; }

        return Vec2{x / Divisor, y / Divisor};
    }

    Vec2& operator*=(float Multiplier) {
        x *= Multiplier;
        y *= Multiplier;
        return *this;
    }

    Vec2& operator/=(float Divisor) {
        if (Divisor == 0.0f) { return *this; }

        x /= Divisor;
        y /= Divisor;
        return *this;
    }

    Vec2 operator+(const Vec2& Other) const {
        return Vec2{x + Other.x, y + Other.y};
    }

    Vec2 operator-(const Vec2& Other) const {
        return *this + (-Other);
    }

    Vec2& operator+=(const Vec2& Other) {
        x += Other.x;
        y += Other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& Other) {
        return *this += (-Other);
    }

    Vec2 operator-() const {
        return Vec2{-x, -y};
    }
};

inline Vec2 operator*(float M, const Vec2& V) {
    return V * M;
}

inline std::ostream& operator<<(
  std::ostream& Stream, const Vec2& V) {
    Stream << "{ x = " << V.x
      << ", y = " << V.y << " }";
    return Stream;
}

#endif //_VECTOR2_H