#include "Globals.h"

std::string Globals::concat(std::initializer_list<std::string> list) {
    std::string s;
    for (auto& i : list) {
        s += i;
    }
    return s;
}
