
#include "Simulation.h"

#include "Flock.h"


// ---------------------- Constructors ----------------- //

Simulation::Simulation()
{
    backgroundColor = sf::Color::Black;
    boidColor = sf::Color::Blue;
}

// ---------------------- Methods ----------------- //

void Simulation::run()
{
    // Creating window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Boids");
    window.setFramerateLimit(60);
    // Render loop

    Flock flock(50);

    flock.setScreenBorders(windowWidth, windowHeight);

    flock.randomizeAllPositions(windowWidth, windowHeight);
    flock.randomizeAllVelocities();

    std::cerr << "# boids: " << flock.boids.size() << '\n';
    std::cerr << "# shapeVecs: " << flock.shapes.size() << '\n';

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(backgroundColor);
        // Draw

        flock.updateAllBoids();
        flock.drawAllShapes(window);

        window.display();

    }

    // end of simulation run()
}
