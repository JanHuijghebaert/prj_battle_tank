#include "App/Utils/Delay.hpp"
#include <time.h>

using namespace App::Utils;

void Delay::wait(int ms) {
    float tDiff  = 0.0f;
    float tStart = (float)clock();
    while (((float)ms / 1000.0f) > ((float)tDiff) / CLOCKS_PER_SEC) {
        tDiff = (float)clock() - tStart;
    }
}
