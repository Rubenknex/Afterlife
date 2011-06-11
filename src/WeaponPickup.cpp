#include "WeaponPickup.h"
 
#include "InputState.h"
 
WeaponPickup::WeaponPickup(World* world, const sf::Vector2f& pos, const WeaponData& data) :
    Entity(world),
    m_Data(data)
{
    SetImage(*IM.GetResource(data.m_ImageFile));
    SetOrigin(GetSize() / 2.0f);
    SetPosition(pos);
 
    setCollidable(true);
    setRadius(5.0f);
}
 
WeaponPickup::~WeaponPickup()
{
 
}
 
void WeaponPickup::update(float dt)
{
    Rotate(0.5f);
}
 
void WeaponPickup::draw(sf::RenderTarget& target)
{
    target.Draw(*this);
}
 
bool WeaponPickup::onCollision(boost::shared_ptr<Entity> other)
{
    switch (other->getType())
    {
    case Entity::PLAYER:
        boost::shared_ptr<Player> player = boost::static_pointer_cast<Player>(other);
        take(player);
        return false;
    }
 
    return false;
}
 
void WeaponPickup::take(boost::shared_ptr<Player> player)
{
    if (g_Input.isKeyDown(sf::Key::E))
    {
        player->setWeapon(m_Data);
 
        setAlive(false);
    }
}
 
