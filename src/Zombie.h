#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED
 
#include <boost/format.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
 
#include "Collision.h"
#include "Decal.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Functions.h"
#include "ResourceManager.h"
#include "Level.h"
#include "Player.h"
 
using boost::shared_ptr;
 
class EntityManager;
class World;
 
class Zombie : public Entity
{
public:
    enum ZombieState
    {
        IDLE,
        ALERTED,
        FADING,
    };
 
public:
    Zombie(World* world, const sf::Image& img, const sf::Vector2f& pos, float speed);
    ~Zombie();
 
    void handleCollision();
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
    bool onCollision(boost::shared_ptr<Entity> other);
 
    void onDeath();
 
    void setState(ZombieState state);
 
    void setPlayerId(int id);
 
private:
    ZombieState mZombieState;
 
    int m_PlayerId;
 
    float mSpeed;
 
    sf::Vector2f mTarget;
    float mMoveDelay;
    float mMoveTimer;
 
    //bool mFading;
    float mFadingTime;
    float mFadingTimer;
};
 
#endif // ZOMBIE_H_INCLUDED
 
