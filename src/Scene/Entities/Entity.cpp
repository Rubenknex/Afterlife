#include "Entity.h"

Entity::Entity(Scene* scene, const std::string& id) :
    m_scene(scene),
    m_id(id),
    m_body(NULL),
    m_script(NULL)
{
    
}

Entity::~Entity()
{
    
}

void Entity::update(float dt) { }

void Entity::draw(sf::RenderTarget& target) { }

std::string Entity::getId()
{
    return m_id;
}

std::string Entity::getType()
{
    return m_type;
}

void Entity::setType(const std::string& type)
{
    m_type = type;
}

bool Entity::hasPhysics()
{
    return m_body != NULL;
}

bool Entity::hasScripting()
{
    return m_script != NULL;
}

Entity* Entity::getUserData()
{
    if (m_body != NULL && m_body->GetUserData() != NULL)
    {
        return static_cast<Entity*>(m_body->GetUserData());
    }
    
    return NULL;
}
