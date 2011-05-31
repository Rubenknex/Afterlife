#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <iostream>
#include <cmath>

#include "../TinyXML/tinyxml.h"

#include "ResourceManager.h"

namespace al
{
    struct Particle
    {
        sf::Vector2f pos;
        sf::Vector2f vel;
        float scale;
        float rotation;
        float timeAlive;
        float lifespan;
        bool alive;
    };

    class ParticleSystem
    {
        public:
            ParticleSystem(const std::string& name);
            ~ParticleSystem();

            void load(const std::string& filename);

            void fire(sf::Vector2f pos);

            void update(float dt);
            void draw(sf::RenderTarget& target);

            const std::string& getName();

            bool operator<(const ParticleSystem& rhs) const;

        private:
            std::string mName;

            sf::Sprite mTexture;

            int mDrawOrder;

            sf::Color mColor;
            float mMinSpeed, mMaxSpeed;
            float mMinAngle, mMaxAngle;
            float mMinScale, mMaxScale;
            float mMinRotation, mMaxRotation;
            float mMinLifespan, mMaxLifespan;
            int mMinParticles, mMaxParticles;

            const static int MAX_PARTICLES = 100;
            Particle mParticles[MAX_PARTICLES];
    };
}

#endif // PARTICLESYSTEM_H_INCLUDED
