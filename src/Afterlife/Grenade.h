#ifndef GRENADE_H_INCLUDED
#define GRENADE_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "AudioPlayer.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Functions.h"
#include "Level.h"
#include "Math.h"
#include "PointLight.h"

using boost::shared_ptr;

namespace al
{
    class EntityManager;
    class World;

    class Grenade : public Entity
    {
        public:
            Grenade(World* world, const sf::Vector2f pos, float angle, float speed);
            ~Grenade();

            void update(float dt);
            void draw(sf::RenderTarget& target);

        private:
            sf::Vector2f mDirection;
            float mSpeed;

            float mExplosionRadius;
            float mDamage;

            float mDetonationDelay;
            float mDetonationTimer;

            std::string m_LightName;

            bool mExploded;
    };
}

#endif // GRENADE_H_INCLUDED
