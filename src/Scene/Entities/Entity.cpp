#include "Entity.h"

#include "../Scene.h"

Entity::Entity(Scene* scene, const std::string& id) :
    m_scene(scene),
    m_id(id),
    m_drawOrder(0),
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

int Entity::getDrawOrder() const
{
    return m_drawOrder;
}

void Entity::setDrawOrder(int drawOrder)
{
    m_drawOrder = drawOrder;
}

sf::Vector2f Entity::getPosition()
{
    if (hasPhysics())
    {
        b2Vec2 bPos = m_body->GetPosition();
        
        return sf::Vector2f(bPos.x * m_scene->getMeterPixelRatio(), bPos.y * m_scene->getMeterPixelRatio());
    }
    
    return sf::Vector2f(0.0f, 0.0f);
}

bool Entity::hasPhysics()
{
    return m_body != NULL;
}

bool Entity::hasScripting()
{
    return m_script != NULL;
}

bool Entity::operator<(const Entity& rhs) const
{
    return rhs.getDrawOrder() < m_drawOrder;
}
