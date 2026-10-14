#include <iostream>
#include "App/Utils/Logger.hpp"

using namespace App::Utils;

void Logger::log(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}
