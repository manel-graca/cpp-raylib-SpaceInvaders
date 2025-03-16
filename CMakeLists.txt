cmake_minimum_required(VERSION 3.31.6)
project(cpp-rlib-spaceinvaders VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

add_executable(cpp-rlib-spaceinvaders 
    src/main.cpp
    src/bullet.cpp
    src/ship.cpp
    src/player.cpp
    src/game.cpp
    src/bulletsManager.cpp
    src/enemiesManager.cpp
    src/colorHelper.cpp
)



target_link_libraries(cpp-rlib-spaceinvaders PRIVATE raylib)
