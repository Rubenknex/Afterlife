#ifndef ENTITYFACTORY_H_INCLUDED
#define ENTITYFACTORY_H_INCLUDED
 
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <SFML/System/Randomizer.hpp>
 
#include "Decal.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Zombie.h"
 
class Decal;
class PlayState;
class World;
class Zombie;
 
class EntityFactory
{
public:
    static boost::shared_ptr<Decal> createBloodDecal(World* world, const sf::Vector2f pos);
    static boost::shared_ptr<Decal> createGrenadeDamageDecal(World* world, const sf::Vector2f pos);
    static boost::shared_ptr<Projectile> createProjectile(World* world, const sf::Vector2f pos, float angle, float speed, float damage);
    static boost::shared_ptr<Zombie> createZombie(World* world, const sf::Vector2f pos);
};
 
#endif // ENTITYFACTORY_H_INCLUDED
 
