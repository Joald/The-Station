#include "Globals.h"
#include "Logging/Logger.h"

std::string Globals::concat(std::initializer_list<std::string_view> list) {
    std::string s;
    for (const auto& i : list) {
        s += i;
    }
    return s;
}