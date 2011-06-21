#include "Parsing.h"

namespace parsing
{
    Color4 color(const std::string& str)
    {
        std::vector<std::string> parts;
        boost::algorithm::split(parts, str, boost::is_any_of(" "));
        
        if (parts.size() < 3)
            std::cout << "Incorrect amount of color components: " << str << std::endl;
        
        Color4 c;
        c.r = atoi(parts[0].c_str());
        c.g = atoi(parts[1].c_str());
        c.b = atoi(parts[2].c_str());
        c.a = 255;
        
        if (parts.size() == 4)
            c.a = atoi(parts[3].c_str());
        
        return c;
    }
    
    Vector2 vector2(const std::string& str)
    {
        std::vector<std::string> parts;
        boost::algorithm::split(parts, str, boost::is_any_of(" "));
        
        Vector2 v;
        v.x = atof(parts[0].c_str());
        v.y = atof(parts[1].c_str());
        
        return v;
    }
    
    std::vector<sf::Vector2f> vertices(const std::string& str)
    {
        std::vector<std::string> parts;
        boost::algorithm::split(parts, str, boost::is_any_of(" "));
        
        std::vector<sf::Vector2f> vertices;
        
        for (int i = 0; i < (int)parts.size(); i += 2)
        {
            sf::Vector2f vertex(atof(parts[i].c_str()), atof(parts[i + 1].c_str()));
            
            vertices.push_back(vertex);
        }
        
        return vertices;
    }
}
