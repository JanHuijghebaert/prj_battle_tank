#ifndef __APP_UTILS_RANDOM__HPP__
#define __APP_UTILS_RANDOM__HPP__

#include <stdint.h>

namespace App::Utils {
class Random {
  public:
    Random();

    /**
     * @brief Returns a random integer between 0 and the specified upper limit (excl.)
     * @param upperlimit The upper limit (excl.)
     * @return A random integer between 0 and upperlimit
     */
    int getRand(int upperlimit);

    /**
     * @brief Returns a random integer between the specified lower and upper limits (excl.)
     * @param lowerlimit The lower limit (excl.)
     * @param upperlimit The upper limit (excl.)
     * @return A random integer between lowerlimit and upperlimit
     */
    int getRand(int lowerlimit, int upperlimit);
};
} // namespace App::Utils

#endif
