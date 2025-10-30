#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    Particle particle = Particle();
    particle.randomize();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        sf::CircleShape shape(particle.radius);
        shape.move(particle.x, particle.y);

        // set the shape color to green
        shape.setFillColor(sf::Color(100, 250, 50));

        window.draw(shape);

        // Update the window
        window.display();

        particle.update(0.1);

        if (particle.x > 800 - particle.radius * 2 || particle.x < 0)
        {
            particle.vx = -particle.vx;
        }
        if (particle.y > 600 - particle.radius * 2 || particle.y < 0)
        {
            particle.vy = -particle.vy;
        }
    }

    return EXIT_SUCCESS;
}