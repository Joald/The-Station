#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include "Logger.h"

namespace Logging {
namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
} // namespace

class Logger::LoggerImpl {
    const std::string_view filename;
    std::optional<std::ofstream> ofstream;
    std::ostream* stream;
    LogLevel level = LogLevel::DEBUG;

    friend class Logger;

public:
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

Logger::LoggerHelper Logger::operator()(LogLevel logLevel, std::source_location loc) const {
    if (DEBUG and logLevel < pimpl->level) {
        using std::chrono::system_clock;
        auto now = system_clock::now();
        auto now_t = system_clock::to_time_t(now);
        auto& str = *pimpl->stream;

        str << std::put_time(std::localtime(&now_t), "[%F %T]") << "[";
        // TODO: if log logLevel == "?"; print function_name
        str << std::filesystem::path{loc.file_name()}.filename().string() << ":" << loc.line()
            << "] ";
    }
    return LoggerHelper(*this);
}


Logger::Logger() noexcept: pimpl(std::make_unique<LoggerImpl>()) {}

std::ostream& Logger::getStream() const {
    return *pimpl->stream;
}

Logger::Logger(std::string_view fileName, bool append)
        : pimpl(std::make_unique<LoggerImpl>(fileName, append)) {}

Logger::~Logger() = default;

Logger::LoggerHelper::~LoggerHelper() {
    logger.getStream() << "\n";
}
} // Logger


void debugAssert(bool assertion, std::string_view msg) {
    if (Logging::Logger::DEBUG and !assertion) {
        std::stringstream s;
        s << "Assertion failed: " << msg;
        throw Logging::AssertionException(s.str());
    }
}
