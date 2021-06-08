#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "Flock.h"


class Simulation
{
private:
    sf::Color boidColor;
    sf::Color backgroundColor;

public:

    unsigned int windowWidth{ 800 };
    unsigned int windowHeight{ 600 };


    // --- Constructors

    Simulation();

    // --- Methods

    void run();
};

#endif
