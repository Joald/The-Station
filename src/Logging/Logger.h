#ifndef THE_STATION_LOGGER_H
#define THE_STATION_LOGGER_H


#include <string>
#include <iosfwd>
#include <source_location>
#include <memory>

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
    class LoggerImpl;
    class LoggerHelper {
        const Logger& logger;
    public:
        constexpr explicit LoggerHelper(const Logger& logger) : logger(logger) {}

        ~LoggerHelper();

        template<class T>
        const Logger::LoggerHelper& operator<<(T&& t) const {
            logger.getStream() << std::forward<T>(t);
            return *this;
        }
    };
    std::unique_ptr<LoggerImpl> pimpl;

    [[nodiscard]] std::ostream& getStream() const;

public:
    Logger() noexcept;
    ~Logger();
    explicit Logger(std::string_view fileName, bool append);

    LoggerHelper operator()(
            LogLevel logLevel = LogLevel::DEBUG,
            std::source_location loc = std::source_location::current()
    ) const;
    friend void ::debugAssert(bool assertion, std::string_view msg);
};

} // Logging

inline static const Logging::Logger logger;

using enum Logging::LogLevel;

#endif //THE_STATION_LOGGER_H