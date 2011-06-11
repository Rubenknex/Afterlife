#include "Particle.h"

namespace al
{
    Particle::Particle()
    {

    }

    Particle::~Particle()
    {

    }

    void Particle::initialize(const sf::Vector2f& pos, const sf::Vector2f vel, float rot, float scale, float lt)
    {
        mPosition = pos;
        mVelocity = vel;
        mRotation = rot;
        mScale = scale;
        mLifetime = lt;
    }

    void Particle::update(float dt)
    {
        mPosition += mVelocity * dt;

        mLifetime -= dt;
    }

    bool Particle::isAlive()
    {
        return mLifetime > 0.0f;
    }
}
