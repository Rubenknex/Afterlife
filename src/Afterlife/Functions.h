#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#define PI 3.14159265

namespace al
{
    template <class T>
    T lerp(T value, T start, T end)
    {
        return start + (end - start) * value;
    }

    template <class T>
    T clamp(T value, T min, T max)
    {
        if (value < min)
            return min;
        else if (value > max)
            return max;

        return value;
    }

    struct Point
    {
        int x;
        int y;
    };

    std::vector<sf::Vector2i> bresenhamLine(int x0, int y0, int x1, int y1);

    sf::Vector2f lerpVector2f(float value, sf::Vector2f start, sf::Vector2f end);
    float vector2fLength(const sf::Vector2f vec);
    float vector2fLengthSq(const sf::Vector2f vec);
    sf::Vector2f vector2fNormalize(const sf::Vector2f vec);
    float vector2fDistSq(const sf::Vector2f v1, const sf::Vector2f v2);

    template <class T>
    void printRect(const sf::Rect<T>& rect)
    {
        std::cout << "Rect(" << rect.Left << "," << rect.Top << "," << rect.Left + rect.Width << "," << rect.Top + rect.Height << ")" << std::endl;
    }

    template <class T>
    void printVector2(const sf::Vector2<T>& vec)
    {
        std::cout << "Vector2(" << vec.x << "," << vec.y << ")" << std::endl;
    }

    float degrees(float radians);
    float radians(float degrees);
}

#endif // FUNCTIONS_H_INCLUDED
