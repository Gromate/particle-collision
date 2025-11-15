# 2D Particle Collision Simulation  
A simple 2D particle-collision simulation implemented in C++ with parallel computing exercise in mind.

## Overview  
This project provides a basic simulation of particles moving and colliding in a 2-dimensional space. It is designed as an exercise for *parallel & distributed computing* — enabling experimentation with parallelisation strategies, synchronization, and performance scalability.

Key features:  
- 2D particles with position, velocity, mass, radius, etc.  
- Elastic collisions between particles and with the boundaries.  

## Building and running 

### Prerequisites  
- A C++17-compatible compiler (e.g., `g++`, `clang++`, or MSVC).  
- CMake (minimum version required as per `CMakeLists.txt`).  

### Build Instructions  
```bash
git clone https://github.com/Spynacz/particle-collision.git
cd particle-collision
mkdir build
cd build
cmake ..
make

