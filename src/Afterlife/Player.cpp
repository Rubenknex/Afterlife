#include "Player.h"

#include "Weapon.h"
#include "World.h"

namespace al
{
    Player::Player(World* world) :
        Entity(world),
        mAnimation(Animation(45, 60, 8, 1, 8, 0.1f)),
        mFlashLight(shared_ptr<SpotLight>(new SpotLight("flashlight", sf::Vector2f(), 0.7f, 280.0f, sf::Color(248, 246, 226), 0.0f, 16.0f))),
        mRightMouseTimer(0.0f),
        mRightMouseDown(false)
    {
        WeaponData weaponData;
        weaponData.load("data/Weapons/ak47.xml");
        mWeapon = new Weapon(weaponData);

        mWeapon->setOwner(this);

        SetPosition(150.0f, 150.0f);
        setSpeed(3.0f);
        SetImage(*IM.GetResource("data/Images/player_gun.png"));
        SetOrigin(25.5f, 30);
        setType(Entity::PLAYER);
        setDrawOrder(4);
        setRadius(25.0f);
        setHealth(100.0f);
        setCollidable(true);

        m_World->getLightManager()->addLight(mFlashLight);
    }

    Player::~Player()
    {
        delete mWeapon;
    }

    void Player::update(float dt)
    {
        if (mRightMouseDown)
        {
            mRightMouseTimer += dt;
        }

        mAnimation.update(dt);
        SetSubRect(mAnimation.getRect());

        sf::Vector2f prevPosition = GetPosition();

        handleInput();

        handleCollision();

        if (abs(math::length(prevPosition - GetPosition())) < 1.0f)
            mAnimation.reset();
        else
            mAnimation.start(Animation::Loop);

        mWeapon->update(dt);

        float rotRadians = math::radians(GetRotation() + 90.0f);
        sf::Vector2f rotNormal(cos(rotRadians), sin(rotRadians));
        mFlashLight->setPosition(GetPosition() + rotNormal * 14.0f);
        mFlashLight->setAngle(GetRotation() + 90.0f);

        // Interpolate the center of the screen towards the position of the player,
        // this looks nice and smooth.
        sf::Vector2f center = g_Window->GetView().GetCenter();
        sf::Vector2f move = math::lerp(center, GetPosition(), 0.05f) - center;
        sf::Vector2f viewSize = g_Window->GetView().GetSize();
        sf::View view(center + move, viewSize);
        g_Window->SetView(view);


        // Get the angle between the mouse cursor and the player.
        sf::Vector2f mousePos(g_Input.getMouseX(), g_Input.getMouseY());
        sf::Vector2f screenPos = g_Window->ConvertCoords(mousePos.x, mousePos.y);
        float rotation = atan2(screenPos.y - GetPosition().y, screenPos.x - GetPosition().x);
        SetRotation(math::degrees(rotation) - 90.0f);

    }

    void Player::handleInput()
    {
        sf::Vector2f movement(0.0f, 0.0f);
        if (g_Input.isKeyDown(sf::Key::A))
            movement.x -= 1.0f;
        if (g_Input.isKeyDown(sf::Key::D))
            movement.x += 1.0f;
        if (g_Input.isKeyDown(sf::Key::W))
            movement.y -= 1.0f;
        if (g_Input.isKeyDown(sf::Key::S))
            movement.y += 1.0f;

        // Do not normalize the movement vector if we have not pressed any keys
        // because it may try to divide by zero.
        if (movement.x != 0.0f || movement.y != 0.0f)
        {
            movement = math::normalize(movement);
            Move(movement * getSpeed());
        }

        if (g_Input.isMouseButtonDown(sf::Mouse::Left))
        {
            mWeapon->fire(*m_World->getEntityManager(), GetPosition(), GetRotation() + 90.0f, 1000.0f);
        }

        if (g_Input.isMouseButtonFirstDown(sf::Mouse::Right))
        {
            mRightMouseDown = true;
        }
        else if (g_Input.isMouseButtonFirstUp(sf::Mouse::Right))
        {
            shared_ptr<Grenade> grenade(new Grenade(m_World, GetPosition(), GetRotation() + 90.0f, mRightMouseTimer * 250.0f));
            m_World->getEntityManager()->add(grenade);

            mRightMouseDown = false;
            mRightMouseTimer = 0.0f;
        }

        if (g_Input.isKeyDown(sf::Key::R))
        {
            mWeapon->reload();
        }
    }

    void Player::handleCollision()
    {
        // Get the rectangle which surrounds the player.
        sf::FloatRect collRect = getRect();
        float lX = collRect.Left;
        float rX = collRect.Left + collRect.Width;
        float tY = collRect.Top;
        float bY = collRect.Top + collRect.Height;

        // Check if the top-left corner collides with tiles.
        if (!m_World->getLevel()->isWalkable(lX, tY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(lX, tY), GetPosition(), getRadius());

            if (colResult.collision)
            {
                Move(colResult.normal * colResult.depth);
            }
        }

        // Check if the top-right corner collides with tiles.
        if (!m_World->getLevel()->isWalkable(rX, tY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(rX, tY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);
        }

        // Check if the bottom-right corner collides with tiles.
        if (!m_World->getLevel()->isWalkable(rX, bY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(rX, bY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);
        }

        // Check if the bottom-left corner collides with tiles.
        if (!m_World->getLevel()->isWalkable(lX, bY))
        {
            CollisionResult colResult = collideRectCircle(m_World->getLevel()->getTileRect(lX, bY), GetPosition(), getRadius());

            if (colResult.collision)
                Move(colResult.normal * colResult.depth);
        }
    }

    void Player::draw(sf::RenderTarget& target)
    {
        target.Draw(*this);

        mWeapon->draw(target);
    }

    bool Player::onCollision(boost::shared_ptr<Entity> other)
    {
        switch (other->getType())
        {
            case Entity::PROJECTILE:
                return false;
            case Entity::ZOMBIE:
                return true;
        }

        return false;
    }

    Weapon* Player::getWeapon()
    {
        return mWeapon;
    }

    void Player::setWeapon(const WeaponData& data)
    {
        mWeapon = new Weapon(data);
        mWeapon->setOwner(this);
    }
}
