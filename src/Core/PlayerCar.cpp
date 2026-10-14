#include "App/Core/PlayerCar.hpp"
#include "App/Core/Entity.hpp"

using namespace App::Core;

PlayerCar::PlayerCar() {
    score   = 0;
    lives   = 3;
    rockets = 10;
}

PlayerCar::~PlayerCar() {
}

void PlayerCar::reset() {
    score   = 0;
    lives   = 3;
    rockets = 10;
    x       = 306;
    y       = 530;
    velX    = 0;
    velY    = 0;
}

int PlayerCar::getNumOfLives() {
    return lives;
}

void PlayerCar::decrementLive() {
    lives = lives - 1;
}

int PlayerCar::getNumOfRockets() {
    return rockets;
}

void PlayerCar::decrementRocket() {
    rockets = rockets - 1;
}
