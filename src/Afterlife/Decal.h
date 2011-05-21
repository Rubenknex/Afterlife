#ifndef DECAL_H_INCLUDED
#define DECAL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "Entity.h"

namespace al
{
    class World;

    class Decal : public Entity
    {
        public:
            Decal(World* world, const sf::Image& img, const sf::Vector2f pos, float lifetime);
            ~Decal();

            void update(float dt);
            void draw(sf::RenderTarget& window);

        private:
            float mLifetime;
            float mFadingTimer;
    };
}

#endif // DECAL_H_INCLUDED
