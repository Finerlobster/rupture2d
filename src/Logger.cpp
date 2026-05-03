
#include <iostream>
#include "Rupture/Logger.h"

Rupture::LogLevel Rupture::Logger::currentLevel = Rupture::LogLevel::DEBUG;

void Rupture::Logger::Log(Rupture::LogLevel level, const char* msg, const char* file, int line){
    if(level >= currentLevel){
        switch(level) {
            case LogLevel::DEBUG:
                std::cout << "[DEBUG] " << msg << " - " << file << ":" << line << std::endl;
                break;
            case LogLevel::INFO:
                std::cout << "[INFO] " << msg << " - " << file << ":" << line << std::endl;
                break;
            case LogLevel::WARN:
                std::cout << "[WARNING] " << msg << " - " << file << ":" << line << std::endl;
                break;
            case LogLevel::ERROR:
                std::cout << "[ERROR] " << msg << " - " << file << ":" << line << std::endl;
                break;
        }
    }
}

void Rupture::Logger::SetLevel(Rupture::LogLevel level){
    currentLevel = level;
}