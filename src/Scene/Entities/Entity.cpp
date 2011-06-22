#include "Entity.h"

#include "../Scene.h"

Entity::Entity(Scene* scene, const std::string& id) :
    m_scene(scene),
    m_id(id),
    m_receiveLight(true),
    m_drawLayer(0),
    m_body(NULL),
    m_script(NULL)
{
    
}

Entity::~Entity()
{
    //std::cout << "Entity Destructor!" << std::endl;
    
    if (hasPhysics())
        m_scene->getB2World()->DestroyBody(m_body);
    
    if (hasScripting())
        delete m_script;
}

void Entity::update(float dt) { }

void Entity::draw(sf::RenderTarget& target) { }

void Entity::handleBeginContact(Entity* entity) { }

void Entity::handleEndContact(Entity* entity) { }

const std::string& Entity::getId() const
{
    return m_id;
}

Entity::EntityType Entity::getType() const
{
    return m_type;
}

void Entity::setType(EntityType type)
{
    m_type = type;
}

int Entity::getDrawLayer() const
{
    return m_drawLayer;
}

void Entity::setDrawLayer(int drawLayer)
{
    m_drawLayer = drawLayer;
}

const sf::Vector2f Entity::getPosition() const
{
    if (hasPhysics())
    {
        b2Vec2 bPos = m_body->GetPosition();
        
        return sf::Vector2f(bPos.x * m_scene->getMeterPixelRatio(), bPos.y * m_scene->getMeterPixelRatio());
    }
    
    return sf::Vector2f(0.0f, 0.0f);
}

void Entity::setPosition(const sf::Vector2f& pos)
{
    if (hasPhysics())
    {
        m_body->SetTransform(b2Vec2(pos.x / m_scene->getMeterPixelRatio(), pos.y / m_scene->getMeterPixelRatio()), m_body->GetAngle());
    }
}

float Entity::getRotation() const
{
    if (hasPhysics())
    {
        return math::degrees(m_body->GetAngle());
    }
    
    return m_sprite.GetRotation();
}

void Entity::setRotation(float rotation)
{
    if (hasPhysics())
    {
        m_body->SetTransform(m_body->GetPosition(), math::radians(rotation));
    }
    
    m_sprite.SetRotation(rotation);
}

const sf::Vector2f& Entity::getScale() const
{
    return m_sprite.GetScale();
}

void Entity::setScale(const sf::Vector2f& scale)
{
    m_sprite.SetScale(scale);
}

b2Body* Entity::getBody() const
{
    return m_body;
}

bool Entity::hasPhysics() const
{
    return m_body != NULL;
}

bool Entity::hasScripting() const
{
    return m_script != NULL;
}

bool Entity::operator<(const Entity& rhs) const
{
    return m_drawLayer < rhs.m_drawLayer;
}
