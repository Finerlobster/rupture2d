#include <iostream>

#include "rupture/Logger.h"

int main() {
    std::cout << "Rupture2D - DEMO: LOGGER" << std::endl;
    
    LOG_INFO("Engine initialized");
    LOG_DEBUG("Debug message");
    LOG_WARN("This is a warning");
    LOG_ERROR("Something went wrong");

    std::cout << "--- Now setting level to WARN ---" << std::endl;
    Rupture::Logger::SetLevel(Rupture::LogLevel::WARN);

    LOG_DEBUG("This should not appear");
    LOG_INFO("This should not appear");
    LOG_WARN("This should appear");
    LOG_ERROR("This should appear");
    
    
    return 0;
}