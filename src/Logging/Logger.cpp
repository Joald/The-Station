#include <sstream>
#include "Logger.h"

namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
}

using Logging::Logger;

void debugAssert(bool assertion, std::string_view msg) {
    if (Logger::DEBUG and !assertion) {
        std::stringstream s;
        s << "Assertion failed: " << msg;
        throw AssertionException(s.str());
    }
}

Logger::LoggerHelper Logger::operator()(LogLevel logLevel, std::source_location loc) const {
    if (DEBUG and logLevel < level) {
        using std::chrono::system_clock;
        auto now = system_clock::now();
        auto now_t = system_clock::to_time_t(now);
        auto& str = *stream;

        str << std::put_time(std::localtime(&now_t), "[%F %T]") << "[";
        // TODO: if log logLevel == "?"; print function_name
        str << std::filesystem::path{loc.file_name()}.filename().string() << ":" << loc.line() << "] ";
    }
    return LoggerHelper(*this);
}
