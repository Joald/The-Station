#include <sstream>
#include "Logger.h"

namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
}

void debugAssert(bool assertion, std::string_view msg) {
    if (DEBUG and !assertion) {
        std::stringstream s;
        s << "Assertion failed: " << msg;
        throw AssertionException(s.str());
    }
}
