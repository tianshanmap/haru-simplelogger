#include "simplelogger/simple_logger.hpp"
namespace haru {
    std::string SimpleLogger::getTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

    template <typename... Args>
    void SimpleLogger::log(LogLevel level, Args... args) {
        if (level < minimumLevel) return; // Filter out lower severity logs

        // std::source_location location = std::source_location::current();
        // std::string filename = std::filesystem::path(location.file_name()).filename().string();
        // std::string logEntry = "[" + getTimestamp() +
        //                        "] [" + levelToString(level) + "] " +
        //                        "[" + filename + ":" + std::to_string(location.line()) + "] ";
        std::string logEntry = "[" + getTimestamp() +
                               "] [" + levelToString(level) + "] ";

        // Print to console
        std::cout << logEntry;
        ([&](const auto& item) {
            std::cout << item << ',';
        }(args), ...);
        std::cout << std::endl;
        // (std::cout << ... << args) << std::endl;
        // std::cout <<  message << std::endl;

        // Save to file
        if (logFile.is_open()) {
            logFile << logEntry;
            ([&](const auto& item) {
                logFile << item << ',';
            }(args), ...);
            logFile << std::endl;
            // logFile << message << std::endl;
        }
    }

    template <typename... Args>
    void SimpleLogger::debug(Args... args) {
        log(DEBUG, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void SimpleLogger::info(Args... args) {
        log(INFO, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void SimpleLogger::warning(Args... args) {
        log(WARNING, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void SimpleLogger::error(Args... args) {
        log(ERROR, std::forward<Args>(args)...);
    }
}
