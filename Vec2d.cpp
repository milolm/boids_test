#include "Vec2d.h"

// Utils

int randomUtil::getRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distrib{ min, max };

    return distrib(generator);
}

// ----------------- Constructors ------------------ //

Vec2d::Vec2d()
{
    x = y = 0;
}

Vec2d::Vec2d(const float& mX, const float& mY)
{
    x = mX;
    y = mY;
}

Vec2d::Vec2d(const Vec2d& vec)
{
    x = vec.x;
    y = vec.y;
}

// ------------- Operator Overload -------------- //

Vec2d Vec2d::operator+(const Vec2d& vec)
{
    return Vec2d(x + vec.x, y + vec.y);
}

Vec2d Vec2d::operator-(const Vec2d& vec)
{
    return Vec2d(x - vec.x, y - vec.y);
}

Vec2d Vec2d::operator*(const float& scalar)
{
    return Vec2d(x * scalar, y * scalar);
}

Vec2d Vec2d::operator/(const float& scalar)
{
    if (scalar == 0.0f) return Vec2d(0.0f, 0.0f);

    return Vec2d(x / scalar, y / scalar);
}

Vec2d& Vec2d::operator+=(const Vec2d& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}
Vec2d& Vec2d::operator-=(const Vec2d& vec)
{
    x -= vec.x;
    y -= vec.y;

    return *this;
}

Vec2d& Vec2d::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vec2d& Vec2d::operator/=(const float& scalar)
{
    if (scalar == 0.0f) return *this;

    x /= scalar;
    y /= scalar;

    return *this;
}
Vec2d& Vec2d::operator=(const Vec2d& vec)
{
    x = vec.x;
    y = vec.y;

    return *this;
}

// -------------------- Functions ------------------- //


double Vec2d::magnitude()
{
    return std::sqrt(x * x + y * y);
}

Vec2d Vec2d::unit()
{
    double mag = magnitude();

    if (mag == 0) return Vec2d(0.f, 0.f);

    return Vec2d(x / mag, y / mag);
}

Vec2d& Vec2d::normalize()
{
    double mag = magnitude();

    if (mag == 0) return *this;

    x /= mag;
    y /= mag;

    return *this;
}


// Vec2d util
Vec2d Vec2d::randomUnitVector()
{
    Vec2d vec;
    vec.x = randomUtil::getRandomNumber(-100, 100);
    vec.y = randomUtil::getRandomNumber(-100, 100);

    return vec.unit();
}


Vec2d& Vec2d::limit(const float& scalar)
{
    normalize();
    x *= scalar;
    y *= scalar;

    return *this;
}

float Vec2d::toDegree(const float& rad)
{
    static constexpr float pi{ 3.1415926535f };

    return rad * (180.f / pi);
}

// Returns true if the vectors magnitude is greater or equal to length
bool Vec2d::magnitudeCmp(const float& length)
{
    if (x <= 0 && y <= 0) return false;

    return ((x * x + y * y) <= (length * length));
}
