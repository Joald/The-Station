#include "Logger.h"

namespace {
class AssertionException : public std::logic_error {
public:
    explicit AssertionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
}

void debugAssert(bool assertion, const std::string& msg) {
    if (DEBUG and !assertion) {
        throw AssertionException("Assertion failed: " + msg);
    }
}
