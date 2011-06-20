#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include <boost/algorithm/string.hpp>
#include <SFML/System.hpp>
#include <vector>

namespace parsing
{
    struct Vector2
    {
        float x, y;
    };
    
    struct Color4
    {
        int r, g, b, a;
    };
    
    Color4 color(const std::string& str);
    
    Vector2 vector2(const std::string& str);
    
    std::vector<sf::Vector2f> vertices(const std::string& str);
}

#endif // PARSING_H_INCLUDED
