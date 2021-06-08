#include "Boid.h"


// ---------------- Constructors -------------------- //
Boid::Boid()
{
    mass = 10.f;
    position = Vec2d(0.f, 0.f);
    velocity = Vec2d(0.f, 0.f);
    acceleration = Vec2d(0.f, 0.f);
}


// ---------------- Methods -------------------- //
void Boid::update(const unsigned int& xBorder, const unsigned int& yBorder)
{
    // Acceleration is  the sum of the forces, mass acts like another weight;
    acceleration /= mass;
    velocity += acceleration;
    velocity.limit(maxSpeed);

    position += velocity;

    wrapAroundBorders(xBorder, yBorder);
    acceleration = Vec2d(0.f, 0.f); // Reset the acceleration everytime it is updated;
}
// Returns true if the distance between us and boid is equal or less than range
bool Boid::isInRange(Boid& boid, const float& range)
{
    // Difference between both positions
    Vec2d d( boid.position - position );

    if (this == &boid) return false;

    return (d.x * d.x) + (d.y * d.y) <= (range * range);
}


void Boid::wrapAroundBorders(const unsigned int& bX, const unsigned int& bY)
{
    if (position.x > bX)
    {
        position.x = 0;
    }
    else if (position.x < 0)
    {
        position.x = bX;
    }

    if (position.y > bY)
    {
        position.y = 0;
    }
    else if (position.y < 0)
    {
        position.y = bY;
    }
}

Vec2d Boid::seek(Vec2d& target)
{
    Vec2d desiredVel = (position - target);
    return (desiredVel - velocity).limit(maxForce);
}

Vec2d Boid::getSeparation(std::vector<Boid>& boids)
{
    Vec2d desired( 0.f, 0.f );

    for (auto& boid : boids)
    {
        Vec2d diff ( position - boid.position );
        if (isInRange(boid, visionLength))
        {
            diff.normalize();
            desired += ((diff * 2)/ (diff.magnitude() * diff.magnitude()));

        }
    }

    return (desired - velocity);
}

Vec2d Boid::getAlignment(std::vector<Boid>& boids)
{

    Vec2d avgVel( 0.f, 0.f );

    for (auto& boid : boids)
    {
        if (isInRange(boid, visionLength))
        {
            avgVel += boid.velocity;
        }
    }

    return (avgVel - velocity);
}

Vec2d Boid::getCohesion(std::vector<Boid>& boids)
{
    Vec2d avgPos( 0.f, 0.f );
    int count{};

    for(auto& boid : boids)
    {
        if (isInRange(boid, visionLength))
        {
            avgPos += boid.position;
            ++count;
        }
    }

    if (count == 0) return Vec2d(0.f, 0.f);

    avgPos /= count;

    Vec2d desiredVel( avgPos - position );

    return (desiredVel - velocity);
}

void Boid::applyFlocking(std::vector<Boid>& boids)
{
    // Weighted all 3 behaviors
    Vec2d wSeparation(getSeparation(boids) * 1.8f);
    Vec2d wAlignment(getAlignment(boids) * 1.85f);
    Vec2d wCohesion(getCohesion(boids) * 0.35f);

    acceleration += wSeparation + wAlignment + wCohesion;
    acceleration.limit(maxForce);
}
