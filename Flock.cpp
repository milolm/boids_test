#include "Flock.h"



//Collision avoidance:
//Only depends on positions not on velocity
//Velocity matching:
//Only depends on velocity and not on position of nearby boids

//------------- Constructors -------------------

Flock::Flock()
{

}

Flock::Flock(const int& initialAmmount)
{
    for(int i{0}; i < initialAmmount; ++i)
    {
        addBoid();
    }





}

// ---------------------- Functions --------------------

void Flock::addBoid()
{
    boids.emplace_back(); // Create a new boid
    addShapes(); // Create a new shape for the boid
}

void Flock::updateAllBoids()
{
    for(boidsSize_t i{0}; i < boids.size(); ++i)
    {
        boids[i].applyFlocking(boids);
        boids[i].update(xBorder, yBorder);
    }

    updateAllShapes();
}

// This function contains the basic shape template for a boid
void Flock::addShapes()
{
    std::vector<sf::Shape*> boidShapes;

    // Circle ( for now just a circle )
    sf::CircleShape* circle{ new sf::CircleShape };

    circle->setPointCount(3u);
    circle->setRadius(6.0f);
    circle->setPosition(0.0f, 0.0f);
    circle->setOrigin(6.0f, 6.0f);
    circle->setFillColor(sf::Color(136, 200, 255));
    circle->setOutlineThickness(1.8f);
    circle->setOutlineColor(sf::Color(20, 53, 86));

    boidShapes.push_back(circle);

    shapes.push_back(boidShapes);

}

void Flock::updateAllShapes()
{
    for(shapesSize_t i{0}; i < shapes.size(); ++i)
    {
        // keep track of the boids position for readability
        Vec2d boidPos(boids[i].position.x, boids[i].position.y);

        // shape[i] is a vector<Shape*>
        // Positioning the circle:
        shapes[i][0]->setPosition(boidPos.x, boidPos.y);

        // Rotating triangle
        auto rotation{ atan2(boids[i].velocity.x, -boids[i].velocity.y) };
        shapes[i][0]->setRotation(Vec2d::toDegree(rotation));
    }
}

void Flock::setAllPositions(const float& x, const float& y)
{
    for(auto& boid : boids)
    {
        boid.position = Vec2d(x, y);
    }
}

void Flock::randomizeAllVelocities()
{
    for(auto& boid : boids)
    {
        boid.velocity = Vec2d::randomUnitVector();
    }
}

void Flock::randomizeAllPositions(const int& xLim, const int& yLim)
{
    for(auto& boid : boids)
    {
        boid.position.x = randomUtil::getRandomNumber(0, xLim);
        boid.position.y = randomUtil::getRandomNumber(0, yLim);
    }
}



void Flock::drawAllShapes(sf::RenderWindow& window)
{
    for(auto& boidShapes : shapes)
    {
        for(auto& shape : boidShapes)
        {
            window.draw(*shape);
        }
    }
}


void Flock::setScreenBorders(const unsigned int& x, const unsigned int& y)
{
    xBorder = x;
    yBorder = y;
}

// just for fun ig
void Flock::createRepulsion(Vec2d& origin, const float& radius, const float& force)
{
    for(auto& boid : boids)
    {
        Vec2d diff( boid.position - origin);
        // Avoid magnitude() because no need to use std::sqrt();
        if ((diff.x * diff.x + diff.y * diff.y) <= (radius * radius))
        {
            boid.acceleration += (diff.unit() * force);
        }

    }
}
