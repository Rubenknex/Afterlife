#ifndef ENTITYMANAGER_H_INCLUDED
#define ENTITYMANAGER_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Collision.h"
#include "Entity.h"
#include "Functions.h"
#include "Math.h"

namespace al
{
    class PlayState;

    typedef boost::shared_ptr<Entity> EntityPtr;

    /// Class that manages the entities in the game and the collisions between them.
    class EntityManager
    {
        public:
            EntityManager();
            ~EntityManager();

            void update(float dt);
            void draw(sf::RenderTarget& target);

            /// Compare two entities by their draw order, used to sort the entities before drawing.
            static bool compareEntities(EntityPtr a, EntityPtr b);

            /// Add an entity.
            int add(EntityPtr e);

            /// Generate a random id which has not been used yet.
            int generateId();

            /// Queries the manager for a vector of entities which are within a certain radius.
            std::vector<EntityPtr> queryRadius(const sf::Vector2f pos, float radius);
            /// Queries the manager for a vector of entities which are of a certain type.
            std::vector<EntityPtr> queryType(Entity::EntityType type);

            /// Returns the entity by id.
            EntityPtr getById(int id);
            /// Removes an entity by id.
            void removeById(int id);

            /// Returns the amount of entities.
            int getCount();

        private:
            std::map<int, EntityPtr> m_Entities;
    };
}

#endif // ENTITYMANAGER_H_INCLUDED
