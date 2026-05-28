//
// Created by developer on 2026-05-27.
//
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <utility>
#include <source_location>

#ifndef HARU_OPENCV_WEB_SIMPLE_LOGGER_H
#define HARU_OPENCV_WEB_SIMPLE_LOGGER_H
enum LogLevel { DEBUG, INFO, WARNING, ERROR };
namespace haru {
    class SimpleLogger {
    private:
        std::ofstream logFile;
        LogLevel minimumLevel;

        SimpleLogger() {
            std::cout << "Loading system settings..." << std::endl;
        }

        // Helper to convert enum to string
        std::string levelToString(LogLevel level) {
            switch (level) {
                case DEBUG: return "DEBUG";
                case INFO: return "INFO";
                case WARNING: return "WARNING";
                case ERROR: return "ERROR";
                default: return "UNKNOWN";
            }
        }
        // Helper to fetch the current system timestamp
        std::string getTimestamp();
    public:
        SimpleLogger(const SimpleLogger&) = delete;
        SimpleLogger& operator=(const SimpleLogger&) = delete;

        // 3. Provide a global static access point
        static SimpleLogger& getInstance() {
            // Thread-safe initialization guaranteed since C++11
            static SimpleLogger instance;
            return instance;
        }

        void configure(const std::string& filename,LogLevel minLevel) {
            this->minimumLevel = minLevel;
            logFile.open(filename, std::ios::app);
        }

        ~SimpleLogger() {
            if (logFile.is_open()) {
                logFile.close();
            }
        }

        // The main logging function
        template <typename... Args>
        void log(LogLevel level, Args... args);
        template <typename... Args>
        void debug(Args... args);
        template <typename... Args>
        void info(Args... args);
        template <typename... Args>
        void warning(Args... args);
        template <typename... Args>
        void error(Args... args);
    };
}
#endif //HARU_OPENCV_WEB_SIMPLE_LOGGER_H
