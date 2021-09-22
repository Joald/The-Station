#ifndef THE_STATION_LOGGER_H
#define THE_STATION_LOGGER_H


#include <string>
#include <ostream>
#include <iostream>
#include <fstream>
#include <source_location>
#include <chrono>
#include <iomanip>
#include <filesystem>

class Logger {
    const inline static bool DEBUG = true;
    const std::string filename;

    std::fstream fstream;
    std::ostream* stream;

    class LoggerHelper {
        Logger& logger;
    public:
        explicit LoggerHelper(Logger& logger) : logger(logger) {}

        ~LoggerHelper() {
            *logger.stream << "\n";
        }

        template <class T>
        LoggerHelper& operator<<(T&& t) {
            *logger.stream << t;
            return *this;
        }

    };


public:
    explicit Logger(std::string_view fileName = "") :
            filename(fileName), fstream() {
        if (!filename.empty()) {
            fstream.open(filename);
            stream = &fstream;
        } else {
            stream = &std::cerr;
        }
    }

    LoggerHelper operator()(std::source_location loc = std::source_location::current());

    friend void debugAssert(bool assertion, std::string_view msg);
};

inline static Logger logger;

void debugAssert(bool assertion, std::string_view msg = "");

#endif //THE_STATION_LOGGER_H