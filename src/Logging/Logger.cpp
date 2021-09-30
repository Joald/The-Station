#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include "Logger.h"

namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
} // namespace

namespace Logging {

class Logger::LoggerImpl {
public:
    const std::string_view filename;
    std::optional<std::ofstream> ofstream;
    std::ostream* stream;
    LogLevel level = LogLevel::DEBUG;

    LoggerImpl() : stream(&std::cerr) {}

    explicit LoggerImpl(std::string_view fileName, bool append) :
            filename(fileName),
            ofstream(std::ofstream{fileName.data(), [&] {
                auto mode = std::ios_base::out;
                if (append) {
                    mode |= std::ios_base::ate;
                }
                return mode;
            }()}),
            stream(&ofstream.value()) {}
};

Logger::Logger() noexcept: pimpl(std::make_unique<LoggerImpl>()) {
    log(INFO, std::source_location::current()) << "Logging to stderr...";
}

std::ostream& Logger::getStream() const {
    return *pimpl->stream;
}

Logger::Logger(std::string_view fileName, bool append)
        : pimpl(std::make_unique<LoggerImpl>(fileName, append)) {
    log(INFO, std::source_location::current()) << "Logging to " << fileName << "...";
}

Logger::~Logger() noexcept = default;

Logger::LoggerHelper::~LoggerHelper() {
    logger.getStream() << "\n";
}
}  // namespace Logging

using Logging::Logger;

void debugAssert(bool assertion, std::string_view msg) {
    if (Logger::DEBUG and !assertion) {
        std::stringstream s;
        s << "Assertion failed: " << msg;
        throw AssertionException(s.str());
    }
}

Logger::LoggerHelper Logger::log(LogLevel logLevel, std::source_location loc) {
    auto& impl = *pimpl;
    if (Logger::DEBUG and logLevel < impl.level) {
        using std::chrono::system_clock;
        auto now = system_clock::now();
        auto now_t = system_clock::to_time_t(now);
        auto& str = *impl.stream;

        str << std::put_time(std::localtime(&now_t), "[%F %T]") << "[";
        // TODO: if log logLevel == "?"; print function_name
        str << std::filesystem::path{loc.file_name()}.filename().string() << ":" << loc.line()
            << "] ";
    }
    return LoggerHelper(*this);
}


Logger::LoggerHelper logger(Logging::LogLevel logLevel, std::source_location loc) {
    static Logger l;
    return l.log(logLevel, loc);
}