#include "ship.hpp"
#include <iostream>
#include <raylib.h>

Ship::Ship(Vector2 position, float speed, Color color)
{
    this->position = position;
    this->speed = speed;
    this->color = color;

    std::cout << "Ship created" << std::endl;
}

void Ship::Draw()
{
}

void Ship::Update()
{
}

void Ship::Reset()
{
}

Vector2 Ship::GetPosition()
{
    return position;
}