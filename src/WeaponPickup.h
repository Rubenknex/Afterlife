#ifndef WEAPONPICKUP_H_INCLUDED
#define WEAPONPICKUP_H_INCLUDED
 
#include <SFML/Graphics.hpp>
 
#include "Entity.h"
#include "Player.h"
#include "Weapon.h"
 
class World;
 
class WeaponPickup : public Entity
{
public:
    WeaponPickup(World* world, const sf::Vector2f& pos, const WeaponData& data);
    ~WeaponPickup();
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
    bool onCollision(boost::shared_ptr<Entity> other);
 
    void take(boost::shared_ptr<Player> player);
 
private:
    WeaponData m_Data;
};
 
#endif // WEAPONPICKUP_H_INCLUDED
 
