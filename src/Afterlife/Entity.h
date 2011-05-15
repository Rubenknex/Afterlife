#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Functions.h"

namespace al
{
    class World;

    /// A base class for all the entities like players and zombies in the game.
    class Entity : public sf::Sprite
    {
        public:
            enum EntityType
            {
                DECAL,
                PLAYER,
                PROJECTILE,
                ZOMBIE,
            };

        public:
            Entity(World* world);
            ~Entity();

            virtual void update(float dt);
            virtual void draw(sf::RenderTarget& target);

            /// Performs any actions that are needed when an entity collides with another one.
            /// Returns a bool wether to correct the entities position or not.
            virtual bool onCollision(boost::shared_ptr<Entity> other);

            World* getWorld();

            void setId(int id);
            int getId();

            EntityType getType();
            void setType(EntityType type);

            float getRadius();
            void setRadius(float radius);

            void setHealth(float health);
            float getHealth();
            void changeHealth(float change);

            int getDrawOrder();
            void setDrawOrder(int drawOrder);

            bool isAlive();
            void setAlive(bool alive);
            virtual void onDeath();

            bool isCollidable();
            void setCollidable(bool collidable);

            bool isVisible();
            void setVisible(bool visible);

            sf::FloatRect getRect();

            bool operator <(const Entity& rhs) const;

        protected:
            World* m_World;

            int m_Id;
            EntityType mType;
            float mRadius;
            float mHealth;
            int mDrawOrder;
            bool mAlive;
            bool mCollidable;
            bool mVisible;
    };
}

#endif // ENTITY_H_INCLUDED
