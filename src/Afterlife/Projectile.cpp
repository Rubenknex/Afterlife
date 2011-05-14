#include "Projectile.h"

#include "EntityManager.h"
#include "ParticleManager.h"
#include "World.h"

namespace al
{
    Projectile::Projectile(World* world, const sf::Vector2f pos, float angle, float speed, float damage) :
        Entity(world)
    {
        setCollidable(true);
        setRadius(1.0f);

        SetPosition(pos);
        mVelocity = sf::Vector2f(cos(radians(angle)) * speed, sin(radians(angle)) * speed);

        mDamage = damage;

        mAlive = true;
    }

    Projectile::~Projectile()
    {

    }

    void Projectile::onCollision(boost::shared_ptr<Entity> other)
    {
        if (other->getType() == Entity::ZOMBIE)
        {
            other->changeHealth(-mDamage);

            m_World->getParticleManager()->fireSystem("blood", GetPosition());

            setAlive(false);
        }
    }

    void Projectile::update(float dt)
    {
        Move(mVelocity * dt);

        if (!m_World->getLevel()->isWalkable(GetPosition().x, GetPosition().y))
        {
            m_World->getParticleManager()->fireSystem("wall_dust", GetPosition());

            setAlive(false);
        }
    }

    void Projectile::draw(sf::RenderTarget& target)
    {
        sf::Shape line = sf::Shape::Line(GetPosition(), GetPosition() - vector2fNormalize(mVelocity) * 8.0f, 2, sf::Color(253, 204, 54));

        target.Draw(line);
    }

    void Projectile::kill()
    {
        mAlive = false;
    }

    float Projectile::getDamage()
    {
        return mDamage;
    }
}
