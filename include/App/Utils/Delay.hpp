#ifndef __APP_UTILS_DELAY__HPP__
#define __APP_UTILS_DELAY__HPP__

#include <stdint.h>

namespace App::Utils {
class Delay {
  public:
    /**
     * @brief Wait for a specified number of milliseconds
     * @param ms The number of milliseconds to wait
     */
    void wait(int ms);
};
} // namespace App::Utils

#endif
