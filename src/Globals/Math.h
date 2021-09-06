#ifndef THE_STATION_MATH_H
#define THE_STATION_MATH_H

#include <algorithm>
#include <cmath>
#include <limits>

#include <SFML/System.hpp>

namespace STEngine::Math {


// Constants
constexpr float PI = 3.1415926535f;

constexpr float PI_2 = 1.5707963267f;

constexpr float epsilon = 0.00001;

constexpr auto maxFloat = std::numeric_limits<float>::max();
constexpr auto minFloat = std::numeric_limits<float>::min();

constexpr sf::Vector2f minVector2f(minFloat, minFloat);
constexpr sf::Vector2f maxVector2f(maxFloat, maxFloat);

// Utility functions

template<typename I>
constexpr I square(I i) {
    return i * i;
}

namespace {
// from https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line#Line_defined_by_two_points
constexpr float distanceFromLineNumerator(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2) {
    auto part1 = (linePoint2.x - linePoint1.x) * (linePoint1.y - point.y);
    auto part2 = (linePoint1.x - point.x) * (linePoint2.y - linePoint1.y);
    return std::abs(part1 - part2);
}
} // namespace

constexpr float dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

constexpr bool areClose(float x, float y) {
    return std::min(x, y) + epsilon > std::max(x, y);
}

constexpr float sqDistance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return square(p1.x - p2.x) + square(p1.y - p2.y);
}

constexpr float distance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt(sqDistance(p1, p2));
}

constexpr float
distanceFromLine(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2, float distance12) {
    return distanceFromLineNumerator(point, linePoint1, linePoint2) / distance12;
}

constexpr float distanceFromLine(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2) {
    return distanceFromLine(point, linePoint1, linePoint2, distance(linePoint1, linePoint2));
}

constexpr float
distanceFromLineNoSqrt(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2, float sqDistance12) {
    return distanceFromLineNumerator(point, linePoint1, linePoint2) / sqDistance12;
}

constexpr float distanceFromLineNoSqrt(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2) {
    return distanceFromLineNoSqrt(point, linePoint1, linePoint2, sqDistance(linePoint1, linePoint2));
}

constexpr float distanceFromLineSegment(const sf::Vector2f& point, const sf::Vector2f& linePoint1, const sf::Vector2f& linePoint2){
    auto sqDist = sqDistance(linePoint1, linePoint2);
    if (areClose(sqDist, 0.f)) {
        return distance(linePoint1, point);
    }
    const float t = std::max(0.f, std::min(1.f, dotProduct(point - linePoint1, linePoint2 - linePoint1) / sqDist));
    const sf::Vector2f projection = linePoint1 + t * (linePoint2 - linePoint1);
    return distance(point, projection);
}


} // STEngine::Math

#endif //THE_STATION_MATH_H
