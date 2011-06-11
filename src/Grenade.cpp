#include "Grenade.h"
 
#include "EntityManager.h"
#include "ParticleManager.h"
#include "World.h"
 
Grenade::Grenade(World* world, const sf::Vector2f pos, float angle, float speed) :
    Entity(world),
    mSpeed(speed),
    mExplosionRadius(100.0f),
    mDamage(110.0f),
    mDetonationDelay(2.0f),
    mDetonationTimer(0.0f),
    mExploded(false)
{
    SetPosition(pos);
    SetImage(*IM.GetResource("data/Images/grenade.png"));
    SetOrigin(GetSize() / 2.0f);
 
    float rads = math::radians(angle);
    mDirection = sf::Vector2f(cos(rads), sin(rads));
}
 
Grenade::~Grenade()
{
    m_World->getLightManager()->removeLight(m_LightName);
}
 
void Grenade::update(float dt)
{
    if (!mExploded)
    {
        mDetonationTimer += dt;
    }
    else
    {
        boost::shared_ptr<Light> light = m_World->getLightManager()->getLightByName(m_LightName);
        light->setIntensity(math::lerp(0.2f, light->getIntensity(), 0.0f));
 
        if (light->getIntensity() <= 0.05f)
            setAlive(false);
    }
 
    Move(mDirection * (mSpeed * dt));
    Rotate(0.2f);
 
    mSpeed = math::lerp(mSpeed, 0.0f, 0.05f);
 
    sf::Vector2f pos = GetPosition();
 
    if (!m_World->getLevel()->getLevelRect().Contains(pos.x, pos.y))
    {
        setAlive(false);
    }
 
    if (!m_World->getLevel()->isWalkable(pos.x, pos.y))
    {
        switch (m_World->getLevel()->getTileSide(pos))
        {
        case Level::LEFT:
            mDirection.x = -mDirection.x;
            break;
        case Level::TOP:
            mDirection.y = -mDirection.y;
            break;
        case Level::RIGHT:
            mDirection.x = -mDirection.x;
            break;
        case Level::BOTTOM:
            mDirection.y = -mDirection.y;
            break;
        }
    }
 
    if (mDetonationTimer >= mDetonationDelay)
    {
        std::vector<boost::shared_ptr<Entity> > affected = m_World->getEntityManager()->queryRadius(GetPosition(), mExplosionRadius);
 
        for (int i = 0; i < affected.size(); i++)
        {
            boost::shared_ptr<Entity> e = affected[i];
 
            if (e->getType() == Entity::ZOMBIE && e->isCollidable() && e->isAlive())
            {
                float damage = (math::distanceSquared(GetPosition(), e->GetPosition()) / (mExplosionRadius * mExplosionRadius)) * mDamage;
 
                e->changeHealth(-damage);
 
                m_World->getParticleManager()->fireSystem("blood_explode", e->GetPosition());
            }
        }
 
        m_World->getParticleManager()->fireSystem("explosion_dust", GetPosition());
        m_World->getParticleManager()->fireSystem("smoke_dark", GetPosition());
        m_World->getEntityManager()->add(EntityFactory::createGrenadeDamageDecal(m_World, GetPosition()));
 
        m_LightName = boost::lexical_cast<std::string>(sf::Randomizer::Random(0, 1000000));
        m_World->getLightManager()->addLight(boost::shared_ptr<PointLight>(new PointLight(m_LightName, GetPosition(), 1.0f, 150.0f, sf::Color(255, 230, 150), 16)));
 
        g_AudioPlayer.playSound("data/Sounds/Weapons/grenade.wav", 90.0f, sf::Randomizer::Random(0.9f, 1.0f));
 
        setVisible(false);
        mExploded = true;
 
        mDetonationTimer = 0.0f;
    }
}
 
void Grenade::draw(sf::RenderTarget& target)
{
    target.Draw(*this);
}
 
