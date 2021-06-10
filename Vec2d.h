#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>
#include <random>

namespace randomUtil
{
    int getRandomNumber(int low, int high);
};

class Vec2d
{
public:
    float x;
    float y;


    // --- Constructors
    Vec2d();
    Vec2d(const float&, const float&);
    Vec2d(const Vec2d&);

    // --- Operator Overload

    Vec2d operator+(const Vec2d&);
    Vec2d operator-(const Vec2d&);
    Vec2d operator*(const float&);
    Vec2d operator/(const float&);

    Vec2d& operator+=(const Vec2d&);
    Vec2d& operator-=(const Vec2d&);
    Vec2d& operator*=(const float&);
    Vec2d& operator/=(const float&);

    Vec2d& operator=(const Vec2d&);

    // --- Functions

    double magnitude();

    Vec2d unit();
    Vec2d& normalize();

    Vec2d& limit(const float&);

    // --- Vec2d util
    static Vec2d randomUnitVector();
    static float toDegree(const float&);
};

#endif
