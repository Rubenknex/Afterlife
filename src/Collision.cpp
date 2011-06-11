#include "Collision.h"

namespace al
{
    CollisionResult collideRectCircle(sf::FloatRect rect, sf::Vector2f cPos, float cRadius)
    {
        CollisionResult result;

        float closestX = math::clamp(cPos.x, rect.Left, rect.Left + rect.Width);
        float closestY = math::clamp(cPos.y, rect.Top, rect.Top + rect.Height);

        sf::Vector2f diff(cPos.x - closestX, cPos.y - closestY);

        if (math::lengthSquared(diff) > cRadius * cRadius)
        {
            result.collision = false;

            return result;
        }

        float length = math::length(diff);

        if (length == 0.0f)
        {
            result.collision = false;

            return result;
        }

        sf::Vector2f normal = math::normalize(diff);

        result.collision = true;
        result.normal = normal;
        result.depth = cRadius - length;

        return result;
    }

    bool collidePointCircle(const sf::Vector2f& point, const sf::Vector2f& cPos, float radius)
    {
        sf::Vector2f difference = point - cPos;

        return math::lengthSquared(difference) < radius * radius;
    }

    bool pointInTriangle(const sf::Vector2f& point, const sf::Vector2f v1, const sf::Vector2f v2, const sf::Vector2f v3)
    {
        bool b1 = (point.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (point.y - v2.y) < 0.0f;
        bool b2 = (point.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (point.y - v3.y) < 0.0f;
        bool b3 = (point.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (point.y - v1.y) < 0.0f;

        return (b1 == b2) && (b2 == b3);
    }
}
