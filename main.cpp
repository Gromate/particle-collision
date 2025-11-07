#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>
#include <math.h>

using namespace std;

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

void check_colission_with_walls(Particle &particle, int window_width, int window_height)
{
    if (particle.x > window_width - particle.radius * 2 || particle.x < 0)
    {
        particle.vx = -particle.vx;
    }
    if (particle.y > window_height - particle.radius * 2 || particle.y < 0)
    {
        particle.vy = -particle.vy;
    }
}

double distance_between_particles(Particle &p1, Particle &p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double distance = sqrt(dx * dx + dy * dy);
    return distance;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");

    vector<Particle> particles;

    for (int i = 0; i < 10; i++)
    {
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

        for (auto &particle : particles)
        {
            sf::CircleShape shape(particle.radius);
            shape.move(particle.x, particle.y);
            check_colission_with_walls(particle, WINDOW_WIDTH, WINDOW_HEIGHT);
            for (auto particle_possible_colission : particles)
            {
                if (distance_between_particles(particle, particle_possible_colission) <= (particle.radius + particle_possible_colission.radius))
                {
                    // check if the particle is the same
                    if (distance_between_particles(particle, particle_possible_colission) > 0.001)
                    {
                        particle.vx = -particle.vx;
                        particle.vy = -particle.vy;
                        particle.x += rand() % 3 - 1;
                    }
                }
            }

            shape.setFillColor(particle.color);
            window.draw(shape);
            particle.update(0.1);
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}