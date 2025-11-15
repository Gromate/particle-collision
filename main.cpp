#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <vector>

#include "Particle.hpp"

using namespace std;

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1200

void handle_wall_collisions(const sf::Window& window,
                            std::vector<Particle>& particles) {
  int window_width = window.getSize().x;
  int window_height = window.getSize().y;

  for (auto& particle : particles) {
    if (particle.x > window_width - particle.radius) {
      particle.x = window_width - particle.radius;
      particle.vx = -particle.vx;
    } else if (particle.x < particle.radius) {
      particle.x = particle.radius;
      particle.vx = -particle.vx;
    }

    if (particle.y > window_height - particle.radius) {
      particle.y = window_height - particle.radius;
      particle.vy = -particle.vy;
    } else if (particle.y < particle.radius) {
      particle.y = particle.radius;
      particle.vy = -particle.vy;
    }
  }
}

void handle_single_collision(Particle& p1, Particle& p2) {
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double dist = sqrt(dx * dx + dy * dy);

  if (dist < p1.radius + p2.radius && dist > 0) {
    double nx = dx / dist;
    double ny = dy / dist;

    double dvx = p2.vx - p1.vx;
    double dvy = p2.vy - p1.vy;

    double dvn = dvx * nx + dvy * ny;

    if (dvn > 0) return;

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

void handle_ball_collisions(std::vector<Particle>& particles) {
  for (size_t i = 0; i < particles.size(); i++) {
    for (size_t j = i + 1; j < particles.size(); j++) {
      handle_single_collision(particles[i], particles[j]);
    }
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                          "Particle collisions");

  vector<Particle> particles;

  for (int i = 0; i < 100; i++) {
    Particle particle = Particle();
    particle.randomize(window.getSize().x, window.getSize().y);
    particles.push_back(particle);
  }

  // Start the game loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));

        handle_wall_collisions(window, particles);
      }
    }

    handle_wall_collisions(window, particles);
    handle_ball_collisions(particles);

    for (auto& particle : particles) {
      particle.update(0.1);
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
