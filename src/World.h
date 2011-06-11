#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
 
#include <boost/shared_ptr.hpp>
#include <iostream>
 
#include "EntityFactory.h"
 
class EntityManager;
class Level;
class LightManager;
class ParticleManager;
class Player;
 
class World
{
public:
    World();
    ~World();
 
    void initialize();
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
    EntityManager* getEntityManager() const;
    LightManager* getLightManager() const;
    ParticleManager* getParticleManager() const;
    Level* getLevel() const;
 
    int getPlayerId() const;
 
private:
    EntityManager* m_EntityManager;
    LightManager* m_LightManager;
    ParticleManager* m_ParticleManager;
 
    Level* m_Level;
 
    int m_PlayerId;
};
 
#endif // WORLD_H_INCLUDED
 
