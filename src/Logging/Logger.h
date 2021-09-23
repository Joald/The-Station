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
#include <optional>

class Logger {
    const inline static bool DEBUG = true;

    const std::string_view filename;
    std::optional<std::ofstream> ofstream;
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
    Logger() noexcept : stream(&std::cerr) {}
    explicit Logger(std::string_view fileName) :
            filename(fileName),
            ofstream(std::ofstream{fileName.data()}),
            stream(&ofstream.value()) {}

    LoggerHelper operator()(std::source_location loc = std::source_location::current());

    friend void debugAssert(bool assertion, std::string_view msg);
};

inline static Logger logger;

void debugAssert(bool assertion, std::string_view msg = "");

#endif //THE_STATION_LOGGER_H