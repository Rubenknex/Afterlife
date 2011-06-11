#include "EntityFactory.h"
 
boost::shared_ptr<Decal> EntityFactory::createBloodDecal(World* world, const sf::Vector2f pos)
{
    std::string decalFile = (boost::format("data/Images/Decals/blood_%1%.png") % sf::Randomizer::Random(1, 4)).str();
    float lifeTime = sf::Randomizer::Random(15.0f, 20.0f);
    boost::shared_ptr<Decal> bloodDecal(new Decal(world, *IM.GetResource(decalFile), pos, lifeTime));
 
    return bloodDecal;
}
 
boost::shared_ptr<Decal> EntityFactory::createGrenadeDamageDecal(World* world, const sf::Vector2f pos)
{
    std::string decalFile = (boost::format("data/Images/Decals/damage_%1%.png") % sf::Randomizer::Random(1, 1)).str();
    float lifeTime = sf::Randomizer::Random(15.0f, 20.0f);
    boost::shared_ptr<Decal> damageDecal(new Decal(world, *IM.GetResource(decalFile), pos, lifeTime));
 
    return damageDecal;
}
 
boost::shared_ptr<Projectile> EntityFactory::createProjectile(World* world, const sf::Vector2f pos, float angle, float speed, float damage)
{
    boost::shared_ptr<Projectile> projectile(new Projectile(world, pos, angle, speed, damage));
 
    return projectile;
}
 
boost::shared_ptr<Zombie> EntityFactory::createZombie(World* world, const sf::Vector2f pos)
{
    std::string zombieImageFile = (boost::format("data/Images/zombie_%1%.png") % sf::Randomizer::Random(1, 5)).str();
    float speed = sf::Randomizer::Random(30.0f, 80.0f);
    boost::shared_ptr<Zombie> zombie(new Zombie(world, *IM.GetResource(zombieImageFile), pos, speed));
 
    return zombie;
}
 
