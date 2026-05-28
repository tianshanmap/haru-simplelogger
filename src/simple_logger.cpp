#include "simplelogger/simple_logger.hpp"
namespace haru {
    std::string SimpleLogger::getTimestamp() {
        std::time_t now = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        return std::string(buf);
    }

    int SimpleLogger::add(int a, int b) {
        return a + b;
    }
    void SimpleLogger::record(std::string a, int b) {
    }

}
