#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "Entity.h"
#include "Functions.h"

namespace al
{
    class EntityManager;
    class World;

    class Projectile : public Entity
    {
        public:
            Projectile(World* world, const sf::Vector2f pos, float angle, float speed, float damage);
            ~Projectile();

            void onCollision(boost::shared_ptr<Entity> other);

            void update(float dt);
            void draw(sf::RenderTarget& target);

            //bool isAlive();
            void kill();

            float getDamage();

        private:
            sf::Vector2f mVelocity;

            float mDamage;

            //bool mAlive;
    };
}

#endif // PROJECTILE_H_INCLUDED
