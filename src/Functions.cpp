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

    std::string randomString()
    {
        return boost::lexical_cast<std::string>(sf::Randomizer::Random(0, 1000000));
    }
}
