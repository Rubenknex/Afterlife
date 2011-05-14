#include "Functions.h"

namespace al
{
    std::vector<sf::Vector2i> bresenhamLine(int x0, int y0, int x1, int y1)
    {
        std::vector<sf::Vector2i> points;

        bool steep = abs(y1 - y0) > abs(x1 - x0);

        if (steep)
        {
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int deltax = x1 - x0;
        int deltay = abs(y1 - y0);
        int error = 0;
        int ystep = 0;
        int y = y0;

        if (y0 < y1)
            ystep = 1;
        else
            ystep = -1;

        for (int x = x0; x < x1; x++)
        {
            if (steep)
            {
                points.push_back(sf::Vector2i(y, x));
            }
            else
            {
                points.push_back(sf::Vector2i(x, y));
            }

            error += deltay;

            if (2 * error >= deltax)
            {
                y += ystep;
                error -= deltax;
            }
        }

        return points;
    }

    sf::Vector2f lerpVector2f(float value, sf::Vector2f start, sf::Vector2f end)
    {
        sf::Vector2f result;
        result.x = start.x + (end.x - start.x) * value;
        result.y = start.y + (end.y - start.y) * value;

        return result;
    }

    float vector2fLength(const sf::Vector2f vec)
    {
        return sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    float vector2fLengthSq(const sf::Vector2f vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }

    sf::Vector2f vector2fNormalize(const sf::Vector2f vec)
    {
        float length = vector2fLength(vec);

        return sf::Vector2f(vec.x / length, vec.y / length);
    }

    float vector2fDistSq(const sf::Vector2f v1, const sf::Vector2f v2)
    {
        float xDist = v2.x - v1.x;
        float yDist = v2.y - v1.y;

        return xDist * xDist + yDist * yDist;
    }

    float degrees(float radians)
    {
        return radians * (180 / PI);
    }

    float radians(float degrees)
    {
        return degrees * (PI / 180);
    }
}
