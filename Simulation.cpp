
#include "Simulation.h"

#include "Flock.h"


// ---------------------- Constructors ----------------- //

Simulation::Simulation()
{
    backgroundColor = sf::Color(201, 230, 255);
    boidColor = sf::Color::Blue;
}

// ---------------------- Methods ----------------- //

void Simulation::run()
{
    // Creating window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Boids");
    window.setFramerateLimit(60);
    // Render loop

    Flock flock(80);

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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R)
                {
                    flock.randomizeAllPositions(windowWidth, windowHeight);
                    flock.randomizeAllVelocities();
                }

                if (event.key.code == sf::Keyboard::Space)
                {
                    sf::Vector2i mPos = sf::Mouse::getPosition(window);
                    Vec2d mouseVec(
                        static_cast<float>( mPos.x ),
                        static_cast<float>( mPos.y )
                    );
                    flock.createRepulsion(mouseVec, 80.f, 1.f);
                }

            }
        }


        window.clear(backgroundColor);
        // Draw

        flock.updateAllBoids();
        flock.drawAllShapes(window);

        window.display();

    }

    // end of simulation run()
}
