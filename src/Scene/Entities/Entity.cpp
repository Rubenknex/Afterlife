#include "Entity.h"

#include "../Scene.h"

Entity::Entity(Scene* scene, const std::string& id) :
    m_scene(scene),
    m_id(id),
    m_body(NULL),
    m_script(NULL)
{
    
}

Entity::~Entity()
{
    std::cout << "Entity Destructor!" << std::endl;
    
    if (hasPhysics())
        m_scene->getB2World()->DestroyBody(m_body);
    
    if (hasScripting())
        delete m_script;
}

void Entity::update(float dt) { }

void Entity::draw(sf::RenderTarget& target) { }

void Entity::handleBeginContact(Entity* entity) { }

void Entity::handleEndContact(Entity* entity) { }

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
