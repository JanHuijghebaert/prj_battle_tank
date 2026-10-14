#include "App/Utils/Random.hpp"
#include <stdlib.h>
#include <time.h>

using namespace App::Utils;

Random::Random() {
    srand(time(NULL));
}

int Random::getRand(int upperlimit) {
    return (rand() % upperlimit);
}

int Random::getRand(int lowerlimit, int upperlimit) {
    return ((rand() % (upperlimit - lowerlimit)) + lowerlimit);
}
