#ifndef THE_STATION_MATH_H
#define THE_STATION_MATH_H

#include <algorithm>
#include <SFML/System.hpp>

const float PI = 3.1415926535f;

const float PI_2 = 1.5707963267f;

const float epsilon = 0.00001;

bool areClose(float x, float y);

const auto maxFloat = std::numeric_limits<float>::max();
const auto minFloat = std::numeric_limits<float>::min();

const sf::Vector2f minVector2f(minFloat, minFloat);
const sf::Vector2f maxVector2f(maxFloat, maxFloat);


#endif //THE_STATION_MATH_H
