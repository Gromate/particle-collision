#include "Particle.hpp"
#include <cmath>

Particle::Particle(double x, double y, double vx, double vy, double radius, double mass)
    : x(x), y(y), vx(vx), vy(vy), radius(radius), mass(mass) {}

void Particle::update(double dt)
{
    x += vx * dt;
    y += vy * dt;
}

Particle Particle::randomize()
{
    x = static_cast<double>(rand() % 100);
    y = static_cast<double>(rand() % 100);
    vx = static_cast<double>((rand() % 200) - 100) / 100.0;
    vy = static_cast<double>((rand() % 200) - 100) / 100.0;
    radius = static_cast<double>((rand() % 20) + 5);
    mass = radius * radius * 3.14; // Proporcjonalna do powierzchni
    color = sf::Color(rand()%255, rand()%255, rand()%255);

    return *this;
}
