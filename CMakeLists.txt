cmake_minimum_required(VERSION 3.16)

project(PhysicsGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(physics_game
    src/integrator.cpp
    src/physical_object.cpp
    src/physics.cpp
    src/simulator.cpp
    src/main.cpp
)

target_include_directories(physics_game PRIVATE
    include
)