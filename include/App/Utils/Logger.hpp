#ifndef __APP_UTILS_LOGGER__HPP__
#define __APP_UTILS_LOGGER__HPP__

#include <string>

namespace App::Utils {
class Logger {
  public:
    /**
     * @brief Log message
     * @param message Message
     */
    static void log(const std::string& message);

    /**
     * @brief Log error message
     * @param message Message
     */
    static void error(const std::string& message);
};
} // namespace App::Utils

#endif
