#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#include "Particle.hpp"

using namespace std;

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

void handle_wall_collisions(Particle& particle) {
    if (particle.x > WINDOW_WIDTH - particle.radius || particle.x < particle.radius) {
        particle.vx = -particle.vx;
    }
    if (particle.y > WINDOW_HEIGHT - particle.radius || particle.y < particle.radius) {
        particle.vy = -particle.vy;
    }

    particle.update(0.1);
}

void handle_ball_collisions(Particle& p1, Particle& p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dist = sqrt(dx * dx + dy * dy);

    if (dist < p1.radius + p2.radius && dist > 0) {
        double nx = dx / dist;
        double ny = dy / dist;

        double dvx = p2.vx - p1.vx;
        double dvy = p2.vy - p1.vy;

        double dvn = dvx * nx + dvy * ny;

        if (dvn > 0)
            return;

        double impulse = 2 * dvn / (p1.mass + p2.mass);

        p1.vx += impulse * p2.mass * nx;
        p1.vy += impulse * p2.mass * ny;
        p2.vx -= impulse * p1.mass * nx;
        p2.vy -= impulse * p1.mass * ny;

        // Separate overlapping particles
        double totalMass = p1.mass + p2.mass;
        double overlap = 0.5 * (p1.radius + p2.radius - dist);
        p1.x -= overlap * (p2.mass / totalMass) * nx;
        p1.y -= overlap * (p2.mass / totalMass) * ny;
        p2.x += overlap * (p1.mass / totalMass) * nx;
        p2.y += overlap * (p1.mass / totalMass) * ny;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Particle collisions");

    vector<Particle> particles;

    for (int i = 0; i < 100; i++) {
        Particle particle = Particle();
        particle.randomize(WINDOW_WIDTH, WINDOW_HEIGHT);
        particles.push_back(particle);
    }

    // Start the game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto& particle : particles) {
            if (particle.x > WINDOW_WIDTH - particle.radius || particle.x < particle.radius) {
                particle.vx = -particle.vx;
            }
            if (particle.y > WINDOW_HEIGHT - particle.radius || particle.y < particle.radius) {
                particle.vy = -particle.vy;
            }

            particle.update(0.1);
        }

        for (size_t i = 0; i < particles.size(); i++) {
            for (size_t j = i + 1; j < particles.size(); j++) {
                handle_ball_collisions(particles[i], particles[j]);
            }
        }

        window.clear();

        for (auto& particle : particles) {
            sf::CircleShape shape(particle.radius);
            shape.setOrigin(shape.getRadius(), shape.getRadius());
            shape.move(particle.x, particle.y);
            shape.setFillColor(particle.color);
            window.draw(shape);
        }

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
