#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

namespace al
{
    struct Point
    {
        int x;
        int y;
    };

    std::vector<sf::Vector2i> bresenhamLine(int x0, int y0, int x1, int y1);

    std::string randomString();

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
}

#endif // FUNCTIONS_H_INCLUDED
