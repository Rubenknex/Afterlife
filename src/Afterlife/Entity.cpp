#include "Entity.h"

namespace al
{
    Entity::Entity(World* world) :
        m_World(world),
        m_Id(-1),
        mRadius(0.0f),
        mHealth(0.0f),
        mDrawOrder(0),
        mAlive(true),
        mVisible(true),
        mCollidable(false)
    {

    }

    Entity::~Entity() { }

    void Entity::update(float dt) { }

    void Entity::draw(sf::RenderTarget& target) { }

    void Entity::onCollision(boost::shared_ptr<Entity> other) { }

    World* Entity::getWorld()
    {
        return m_World;
    }

    void Entity::setId(int id)
    {
        m_Id = id;
    }

    int Entity::getId()
    {
        return m_Id;
    }

    Entity::EntityType Entity::getType()
    {
        return mType;
    }

    void Entity::setType(EntityType type)
    {
        mType = type;
    }

    float Entity::getRadius()
    {
        return mRadius;
    }

    void Entity::setRadius(float radius)
    {
        mRadius = radius;
    }

    void Entity::setHealth(float health)
    {
        mHealth = health;

        if (mHealth < 0.0f && mAlive)
            onDeath();
    }

    float Entity::getHealth()
    {
        return mHealth;
    }

    void Entity::changeHealth(float change)
    {
        setHealth(mHealth + change);
    }

    int Entity::getDrawOrder()
    {
        return mDrawOrder;
    }

    void Entity::setDrawOrder(int drawOrder)
    {
        mDrawOrder = drawOrder;
    }

    bool Entity::isAlive()
    {
        return mAlive;
    }

    void Entity::setAlive(bool alive)
    {
        mAlive = alive;
    }

    void Entity::onDeath()
    {
        mAlive = false;
    }

    bool Entity::isCollidable()
    {
        return mCollidable;
    }

    void Entity::setCollidable(bool collidable)
    {
        mCollidable = collidable;
    }

    bool Entity::isVisible()
    {
        return mVisible;
    }

    void Entity::setVisible(bool visible)
    {
        mVisible = visible;
    }

    sf::FloatRect Entity::getRect()
    {
        sf::Vector2f size = GetSize();
        sf::Vector2f pos = GetPosition() - size / 2.0f;

        sf::FloatRect rect(pos.x, pos.y, size.x, size.y);

        //printRect<float>(rect);

        return rect;
    }

    bool Entity::operator <(const Entity& rhs) const
    {
        return mDrawOrder < rhs.mDrawOrder;
    }
}
