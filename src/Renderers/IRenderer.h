#ifndef IRENDERER_H_INCLUDED
#define IRENDERER_H_INCLUDED

#include <SFML/Graphics.hpp>

class IRenderer
{
public:
    virtual void draw(sf::RenderTarget& target) = 0;
};

#endif // IRENDERER_H_INCLUDED
