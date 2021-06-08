#include "Boid.h"


// ---------------- Constructors -------------------- //
Boid::Boid()
{
    position = Vec2d(0.f, 0.f);
    velocity = Vec2d(0.f, 0.f);
    acceleration = Vec2d(0.f, 0.f);
}


// ---------------- Methods -------------------- //
void Boid::update(const unsigned int& xBorder, const unsigned int& yBorder)
{
    velocity += acceleration;
    velocity.limit(maxSpeed);

    position += velocity;

    wrapAroundBorders(xBorder, yBorder);
    acceleration = Vec2d(0.f, 0.f); // Reset the acceleration everytime it is updated;
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
    Vec2d steer(0.f, 0.f);

    for (auto& boid : boids)
    {
        Vec2d diff(boid.position - position);

        // Checks if magnitude of diff is <= than visionLength
        if (diff.magnitudeCmp(visionLength / 2))
        {
            steer += diff;
            steer / diff.magnitude();
        }
    }
    steer.normalize();

    steer += position;

    return seek(steer);
}

Vec2d Boid::getCohesion(std::vector<Boid>& boids)
{
    Vec2d avgPos(0.f, 0.f);
    int count{};

    for(auto& boid : boids)
    {
        Vec2d diff(boid.position - position);
        if (diff.magnitudeCmp(visionLength))
        {
            avgPos += boid.position;
            ++count;
        }
    }
    avgPos /= count;

    return seek(avgPos);
}

Vec2d Boid::getAlignment(std::vector<Boid>& boids)
{
    Vec2d avgVel(0.f, 0.f);
    int count{};

    for(auto& boid : boids)
    {
        Vec2d diff(boid.position - position);

        if (diff.magnitudeCmp(visionLength))
        {
            avgVel += boid.velocity;
        }
    }
    avgVel /= count;

    return (avgVel - velocity).limit(maxForce);
}
