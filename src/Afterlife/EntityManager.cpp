#include "EntityManager.h"

namespace al
{
    EntityManager::EntityManager()
    {

    }

    EntityManager::~EntityManager()
    {

    }

    void EntityManager::update(float dt)
    {
        std::map<int, EntityPtr>::iterator it;
        for (it = m_Entities.begin(); it != m_Entities.end(); it++)
        {
            if (it->second->isAlive())
                it->second->update(dt);
            else
            {
                m_Entities.erase(it);
            }
        }

        std::map<int, EntityPtr>::iterator it2;
        for (it = m_Entities.begin(); it != m_Entities.end(); it++)
        {
            for (it2 = m_Entities.begin(); it2 != m_Entities.end(); it2++)
            {
                EntityPtr e1 = it->second;
                EntityPtr e2 = it2->second;

                if (it == it2 || !e1->isAlive() || !e2->isAlive() || !e1->isCollidable() || !e2->isCollidable())
                    continue;

                sf::Vector2f diff = e2->GetPosition() - e1->GetPosition();
                float distance = math::length(diff);

                if (distance < e1->getRadius() + e2->getRadius())
                {
                    float overlap = (e1->getRadius() + e2->getRadius()) - distance;

                    diff = math::normalize(diff) * (overlap / 2);

                    if (e1->onCollision(e2))
                        e1->Move(-diff);
                    if (e2->onCollision(e1))
                        e2->Move(diff);
                }
            }
        }
    }

    void EntityManager::draw(sf::RenderTarget& target)
    {
        std::vector<EntityPtr> sortedEntities;
        std::map<int, EntityPtr>::iterator it;
        for (it = m_Entities.begin(); it != m_Entities.end(); it++)
        {
            sortedEntities.push_back(it->second);
        }

        std::sort(sortedEntities.begin(), sortedEntities.end(), compareEntities);

        //std::cout << sortedEntities.size() << std::endl;

        for (int i = 0; i < (int)sortedEntities.size(); i++)
        {
            if (sortedEntities[i]->isVisible())
                sortedEntities[i]->draw(target);
        }
    }

    bool EntityManager::compareEntities(EntityPtr a, EntityPtr b)
    {
        return a->getDrawOrder() < b->getDrawOrder();
    }

    int EntityManager::add(EntityPtr e)
    {
        int id = generateId();

        e->setId(id);
        m_Entities.insert(std::pair<int, EntityPtr>(id, e));

        return id;
    }

    int EntityManager::generateId()
    {
        int id = -1;

        do
        {
            id = sf::Randomizer::Random(0, 100000);
        }
        while (m_Entities.find(id) != m_Entities.end());

        return id;
    }

    std::vector<EntityPtr> EntityManager::queryRadius(const sf::Vector2f pos, float radius)
    {
        float radiusSq = radius * radius;

        std::vector<EntityPtr> entities;

        std::map<int, EntityPtr>::iterator it;
        for (it = m_Entities.begin(); it != m_Entities.end(); it++)
        {
            float distSq = math::distanceSquared(pos, it->second->GetPosition());

            if (distSq < radiusSq)
                entities.push_back(it->second);
        }

        return entities;
    }

    std::vector<EntityPtr> EntityManager::queryType(Entity::EntityType type)
    {
        std::vector<EntityPtr> entities;

        std::map<int, EntityPtr>::iterator it;
        for (it = m_Entities.begin(); it != m_Entities.end(); it++)
        {
            if (it->second->getType() == type)
                entities.push_back(it->second);
        }

        return entities;
    }

    EntityPtr EntityManager::getById(int id)
    {
        std::map<int, EntityPtr>::iterator it = m_Entities.find(id);

        if (it != m_Entities.end())
            return it->second;

        return boost::shared_ptr<Entity>();
    }

    void EntityManager::removeById(int id)
    {
        std::map<int, EntityPtr>::iterator it = m_Entities.find(id);

        if (it != m_Entities.end())
            m_Entities.erase(it);
    }

    int EntityManager::getCount()
    {
        return (int)m_Entities.size();
    }
}
