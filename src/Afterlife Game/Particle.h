#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <SFML/System/Vector2.hpp>

namespace al
{
    class Particle
    {
        public:
            Particle();
            ~Particle();

            void initialize(const sf::Vector2f& pos, const sf::Vector2f vel, float rot, float scale, float lt);

            void update(float dt);

            bool isAlive();

        public:
            sf::Vector2f mPosition;
            sf::Vector2f mVelocity;
            float mRotation;
            float mScale;
            float mLifetime;
    };
}

#endif // PARTICLE_H_INCLUDED
