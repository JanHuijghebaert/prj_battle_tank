#include "App/Core/Entity.hpp"

using namespace App::Core;

Entity::Entity() {
    x    = 0;
    y    = 0;
    velX = 0;
    velY = 0;
}

Entity::~Entity() {
}

void Entity::move(int limitUp, int limitRight, int limitDown, int limitLeft) {
    x = x + velX;
    if (x < limitLeft) x = limitLeft;
    if (x > limitRight) x = limitRight;
    y = y + velY;
    if (y < limitUp) y = limitUp;
    if (y > limitDown) y = limitDown;
}

void Entity::move() {
    x = x + velX;
    y = y + velY;
}

void Entity::setCenter(int screen_width, int screen_height, int width, int height) {
    x = (screen_width / 2) - (width / 2);
    y = (screen_height / 2) - (height / 2);
}

void Entity::setScorePosition(int screen_width, int width) {
    x = screen_width - width - 5;
}
