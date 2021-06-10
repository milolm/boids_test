#ifndef FLOCK_H
#define FLOCK_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Boid.h"

using boidsSize_t = std::vector<Boid>::size_type;
using shapesSize_t = std::vector<std::vector<sf::Shape*>>::size_type;


// The shapes in shapes[i] correspond to boids[i]

// Shapes structure
//shapes[i][0] -- CIRCLE -- The default circle for now




class Flock
{
public:
    std::vector<Boid> boids;
    std::vector<std::vector<sf::Shape*>> shapes;

    unsigned int xBorder; // To make sure boids wrap around screen borders
    unsigned int yBorder;

    // Boid config
    float boidRadius{ 6.f };

    // Constructors

    Flock();
    Flock(const int&);

    // Functions

    void addBoid();
    void addShapes();

    void updateAllBoids();
    void updateAllShapes();

    void setAllPositions(const float&, const float&);
    void randomizeAllVelocities();
    void randomizeAllPositions(const int&, const int&);

    void drawAllShapes(sf::RenderWindow& window);

    void setScreenBorders(const unsigned int&, const unsigned int&);

    void createRepulsion(Vec2d&, const float&, const float&);
};


#endif
