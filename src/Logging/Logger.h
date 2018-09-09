#ifndef THE_STATION_LOGGER_H
#define THE_STATION_LOGGER_H


#include <string>
#include <ostream>
#include <iostream>
#include <fstream>

const bool DEBUG = true;

class Logger {
    const std::string filename;

    std::fstream fstream;
public:
    explicit Logger(const std::string& filename = "") :
      filename(filename), fstream() {
        if (!filename.empty()) {
            fstream.open(filename);
        }
    }

    template<class T>
    void log(const T& t) {
        if (DEBUG) {
            if (filename.empty()) {
                std::cerr << t;
            } else {
                fstream << t;
            }
        }
    }

    void endLine() {
        log("\n");
    }
};

template<class... Args>
Logger& logger(Args... args) {
    static Logger logger(args...);
    return logger;
}

template<class T>
void debugLog(const T& t) {
    logger().log(t);
    logger().endLine();
}

template<class T, class... Rest>
void debugLog(const T& t, Rest... rest) {
    logger().log(t);
    debugLog(rest...);
}


#endif //THE_STATION_LOGGER_H
