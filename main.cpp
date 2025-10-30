#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>

using namespace std;

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");

    vector<Particle> particles;

    for (int i=0; i< 400; i++) {
        Particle particle = Particle();
        particle.randomize();
        particles.push_back(particle);
    }
    // Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        for (auto& particle : particles) {
            sf::CircleShape shape(particle.radius);
            shape.move(particle.x, particle.y);

            shape.setFillColor(particle.color);
            window.draw(shape);

            if (particle.x > WINDOW_WIDTH - particle.radius * 2 || particle.x < 0)
            {
                particle.vx = -particle.vx;
            }
            if (particle.y > WINDOW_HEIGHT - particle.radius * 2 || particle.y < 0)
            {
                particle.vy = -particle.vy;
            }

            particle.update(0.1);
        }

        // Update the window
        window.display();

    }

    return EXIT_SUCCESS;
}