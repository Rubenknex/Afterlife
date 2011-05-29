#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <cmath>

namespace al
{
    namespace math
    {
        template <class T>
        T lerp(T start, T end, T val)
        {
            return start + (end - start) * val;
        }

        template <class T>
        sf::Vector2<T> lerp(sf::Vector2<T> start, sf::Vector2<T> end, float val)
        {
            float x = start.x + (end.x - start.x) * val;
            float y = start.y + (end.y - start.y) * val;

            return sf::Vector2<T>(x, y);
        }

        template <class T>
        sf::Vector2<T> normalize(sf::Vector2<T> v)
        {
            float len = sqrt(v.x * v.x + v.y * v.y);

            return sf::Vector2<T>(v.x / len, v.y / len);
        }

        template <class T>
        T length(sf::Vector2<T> v)
        {
            return sqrt(v.x * v.x + v.y * v.y);
        }

        template <class T>
        T lengthSquared(sf::Vector2<T> v)
        {
            return v.x * v.x + v.y * v.y;
        }

        template <class T>
        T distance(sf::Vector2<T> v1, sf::Vector2<T> v2)
        {
            T diffX = v2.x - v1.x;
            T diffY = v2.y - v1.y;

            return sqrt(diffX * diffX + diffY * diffY);
        }

        template <class T>
        T distanceSquared(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
        {
            T diffX = v2.x - v1.x;
            T diffY = v2.y - v1.y;

            return diffX * diffX + diffY * diffY;
        }

        template <class T>
        T clamp(T value, T min, T max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;

            return value;
        }

        template <class T>
        T radians(T degrees)
        {
            return degrees * (M_PI / 180);
        }

        template <class T>
        T degrees(T radians)
        {
            return radians * (180 / M_PI);
        }
    }
}

#endif // MATH_H_INCLUDED
