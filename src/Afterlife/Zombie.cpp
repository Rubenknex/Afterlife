#include "Zombie.h"

#include "EntityManager.h"
#include "ParticleManager.h"
#include "World.h"

namespace al
{
    Zombie::Zombie(World* world, const sf::Image& img, const sf::Vector2f& pos, float speed) :
        Entity(world),
        mZombieState(IDLE),
        mSpeed(speed),
        mTarget(pos),
        mMoveDelay(2.0f),
        mMoveTimer(0.0f),
        mFadingTime(1.0f),
        mFadingTimer(0.0f)
    {
        SetImage(img);
        SetPosition(pos);
        SetSubRect(sf::IntRect(0, 0, 45, 60));
        SetOrigin(25.5f, 30);
        setDrawOrder(4);
        setRadius(25.0f);
        setHealth(100.0f);
        setType(Entity::ZOMBIE);
        setCollidable(true);
    }

    Zombie::~Zombie()
    {

    }

    void Zombie::handleCollision()
    {
        sf::FloatRect collRect = getRect();
        float lX = collRect.Left;
        float rX = collRect.Left + collRect.Width;
        float tY = collRect.Top;
        float bY = collRect.Top + collRect.Height;

        if (!m_World->getLevel()->isWalkable(lX, tY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(lX, tY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);

            //std::cout << "handled collision" << std::endl;
        }

        if (!m_World->getLevel()->isWalkable(rX, tY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(rX, tY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);

            //std::cout << "handled collision" << std::endl;
        }

        if (!m_World->getLevel()->isWalkable(rX, bY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(rX, bY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);

            //std::cout << "handled collision" << std::endl;
        }

        if (!m_World->getLevel()->isWalkable(lX, bY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(lX, bY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);

            //std::cout << "handled collision" << std::endl;
        }
    }

    void Zombie::update(float dt)
    {
        if (mZombieState == IDLE)
        {
            mMoveTimer += dt;

            if (mMoveTimer > mMoveDelay)
            {
                float angle = radians(sf::Randomizer::Random(0.0f, 360.0f));
                sf::Vector2f direction(cos(angle), sin(angle));
                mTarget = GetPosition() + direction * sf::Randomizer::Random(100.0f, 150.0f);

                mMoveTimer = 0.0f;
            }

            sf::Vector2f direction = mTarget - GetPosition();

            if (vector2fLength(direction) > 1.0f)
            {
                Move(vector2fNormalize(direction) * (mSpeed * dt));
            }

            SetRotation(degrees(atan2(direction.y, direction.x)) - 90.0f);

            sf::Vector2f playerDistance = m_World->getEntityManager()->getById(m_World->getPlayerId())->GetPosition() - GetPosition();

            if (vector2fLength(playerDistance) < 200.0f)
            {
                bool seePlayer = !m_World->getLevel()->rayCast(GetPosition(), GetPosition() + playerDistance);

                if (seePlayer)
                    mZombieState = ALERTED;
            }
        }
        else if (mZombieState == ALERTED)
        {
            sf::Vector2f playerDirection = vector2fNormalize(m_World->getEntityManager()->getById(m_World->getPlayerId())->GetPosition() - GetPosition());
            Move(playerDirection * (mSpeed * dt));

            SetRotation(degrees(atan2(playerDirection.y, playerDirection.x)) - 90.0f);
        }

        sf::Vector2f pos = GetPosition();
        if (pos.x < 0)
            pos.x = 0;
        if (pos.y < 0)
            pos.y = 0;

        if (mZombieState != FADING)
        {
            handleCollision();
        }
        else
        {
            if (mFadingTimer < mFadingTime)
            {
                mFadingTimer += dt;

                int alpha = clamp(255 - ((mFadingTimer / mFadingTime) * 255), 0.0f, 255.0f);
                SetColor(sf::Color(255, 255, 255, alpha));
            }
            else
            {
                setAlive(false);
            }
        }
    }

    void Zombie::draw(sf::RenderTarget& target)
    {
        target.Draw(*this);

        //sf::Shape circle = sf::Shape::Circle(GetPosition(), getRadius(), sf::Color::Red);
        //window.Draw(circle);
    }

    bool Zombie::onCollision(boost::shared_ptr<Entity> other)
    {
        switch (other->getType())
        {
            case Entity::PLAYER:
                return true;
            case Entity::PROJECTILE:
                //std::cout << "Blood!" << std::endl;
                m_World->getParticleManager()->fireSystem("blood", GetPosition() + sf::Vector2f(sf::Randomizer::Random(-15.0f, 15.0f), sf::Randomizer::Random(-15.0f, 15.0f)));

                return false;
            case Entity::ZOMBIE:
                return true;
        }

        return false;
    }

    void Zombie::onDeath()
    {
        m_World->getEntityManager()->add(EntityFactory::createBloodDecal(m_World, GetPosition()));

        mZombieState = FADING;
        setCollidable(false);
    }

    void Zombie::setState(ZombieState state)
    {
        mZombieState = state;
    }
}
