#include "Math.h"

bool areClose(float x, float y) {
    return std::min(x, y) + epsilon > std::max(x, y);
}
