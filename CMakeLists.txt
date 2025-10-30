cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(particles-collision)

include(FetchContent)

# Define where to fetch Catch2 from
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.6.0  # Or the latest stable tag
)
FetchContent_MakeAvailable(Catch2)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SOURCES
    Particle.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
# find_package(SDL2 REQUIRED)
# find_package(Armadillo REQUIRED) 
find_package(Catch2 REQUIRED)


# Add global definitions
add_definitions("-Wall")
# include_directories(${SDL2_INCLUDE_DIR})
# include_directories(${ARMADILLO_INCLUDE_DIRS})


# add_executable(tests ../tests/test.cpp ${SOURCES})
# target_link_libraries(tests Catch2::Catch2WithMain)
add_executable(particles-collision main.cpp ${SOURCES})

set_property(TARGET particles-collision PROPERTY CXX_STANDARD 17)
install(TARGETS particles-collision RUNTIME DESTINATION bin)

# target_link_libraries(particles-collision ${SDL2_LIBRARIES})
# target_link_libraries(particles-collision ${ARMADILLO_LIBRARIES})
target_link_libraries(particles-collision PRIVATE SFML::Graphics)

# target_link_libraries(tests ${ARMADILLO_LIBRARIES})
