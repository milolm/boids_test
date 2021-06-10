#ifndef BOID_H
#define BOID_H

#include "Vec2d.h"

class Boid
{
public:
    Vec2d position;
    Vec2d velocity;
    Vec2d acceleration;
    float mass;

    float maxSpeed{ 0.75f };
    float maxForce{ 0.3f };

    float visionLength{ 50.f };


    // --- Constructor
    Boid();

    // --- Methods

    // update method takes screenWidth and screenHeight as parameters
    // this is for the boids to wrap around the borders of the window
    void update(const unsigned int&, const unsigned int&);

    // Keeps the boid inside the borders by making it wrap around borders
    void wrapAroundBorders(const unsigned int&, const unsigned int&);

    // Boid behavior
    Vec2d seek(Vec2d& target);

    Vec2d getSeparation(std::vector<Boid>&);
    Vec2d getCohesion(std::vector<Boid>&);
    Vec2d getAlignment(std::vector<Boid>&);
    void applyFlocking(std::vector<Boid>&);

    bool isInRange(Boid&, const float&);
};

#endif
