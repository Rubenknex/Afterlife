#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Functions.h"

namespace al
{
    struct CollisionResult
    {
        bool collision;
        sf::Vector2f normal;
        float depth;
    };

    CollisionResult collideRectCircle(sf::FloatRect rect, sf::Vector2f cPos, float cRadius);

    bool collidePointCircle(const sf::Vector2f& point, const sf::Vector2f& cPos, float radius);

    bool pointInTriangle(const sf::Vector2f& point, const sf::Vector2f v1, const sf::Vector2f v2, const sf::Vector2f v3);
}

#endif // COLLISION_H_INCLUDED
