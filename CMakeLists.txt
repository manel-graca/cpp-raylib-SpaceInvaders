cmake_minimum_required(VERSION 3.21.7)
project(cpp-rlib-spaceinvaders VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

add_executable(cpp-rlib-spaceinvaders 
    src/main.cpp
    src/colorHelper.cpp
    src/game.cpp
    src/bullet.cpp
    src/bulletsManager.cpp
    src/ship.cpp
    src/player.cpp
    src/enemy.cpp
    src/obstacle.cpp
    src/explosionFX.cpp
)

target_link_libraries(cpp-rlib-spaceinvaders PRIVATE raylib)
