#include <sstream>
#include "Logger.h"

namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
}

void debugAssert(bool assertion, std::string_view msg) {
    if (Logger::DEBUG and !assertion) {
        std::stringstream s;
        s << "Assertion failed: " << msg;
        throw AssertionException(s.str());
    }
}

Logger::LoggerHelper Logger::operator()(std::source_location loc) {
    if (DEBUG) {
        auto now = std::chrono::system_clock::now();
        auto now_t = std::chrono::system_clock::to_time_t(now);
        auto& str = *stream;

        str << std::put_time(std::localtime(&now_t), "[%F %T]") << "[";
        // TODO: if log level == "?"; print function_name
        str << std::filesystem::path{loc.file_name()}.filename().string() << ":" << loc.line() << "] ";
    }
    return LoggerHelper(*this);
}
