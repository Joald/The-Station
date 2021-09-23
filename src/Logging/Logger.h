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

void debugAssert(bool assertion, std::string_view msg = "");

namespace Logging {
enum class LogLevel {
    OFF,
    FATAL,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
};


class Logger {
    const inline static bool DEBUG = true;

    const std::string_view filename;
    std::optional<std::ofstream> ofstream;
    std::ostream* stream;
    LogLevel level = LogLevel::DEBUG;

    class LoggerHelper {
        Logger& logger;
    public:
        explicit LoggerHelper(Logger& logger) : logger(logger) {}

        ~LoggerHelper() {
            *logger.stream << "\n";
        }

        template<class T>
        LoggerHelper& operator<<(T&& t) {
            *logger.stream << std::forward<T>(t);
            return *this;
        }

    };

public:
    Logger() noexcept: stream(&std::cerr) {}

    explicit Logger(std::string_view fileName) :
            filename(fileName),
            ofstream(std::ofstream{fileName.data()}),
            stream(&ofstream.value()) {}

    LoggerHelper operator()(LogLevel logLevel = LogLevel::DEBUG, std::source_location loc = std::source_location::current());

    friend void ::debugAssert(bool assertion, std::string_view msg);
};

} // Logging

inline static Logging::Logger logger;

using enum Logging::LogLevel;

#endif //THE_STATION_LOGGER_H