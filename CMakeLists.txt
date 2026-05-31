cmake_minimum_required(VERSION 3.16)

project(PhysicsGame)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(physics_game
    src/main.cpp
    src/backend/integrator.cpp
    src/backend/physical_object.cpp
    src/backend/physics.cpp
    src/backend/simulator.cpp

    src/frontend/mainwindow.cpp

    src/interface/interface.cpp
)

target_include_directories(physics_game PRIVATE
    include/backend/
    include/frontend/
    include/interface/
)

target_link_libraries(physics_game PRIVATE
    Qt6::Widgets
)
