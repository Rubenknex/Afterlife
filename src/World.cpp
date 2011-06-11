#include "World.h"
 
#include "EntityManager.h"
#include "LightManager.h"
#include "ParticleManager.h"
#include "Player.h"
#include "Level.h"
 
World::World() :
    m_EntityManager(new EntityManager()),
    m_LightManager(new LightManager()),
    m_ParticleManager(new ParticleManager()),
    m_Level(new Level()),
    m_PlayerId(-1)
{
 
}
 
World::~World()
{
    delete m_EntityManager;
    delete m_LightManager;
    delete m_ParticleManager;
 
    delete m_Level;
}
 
void World::initialize()
{
    m_LightManager->setAmbientColor(sf::Color(100, 100, 100));
 
    m_ParticleManager->loadSystem("data/ParticleSystems/blood.xml", "blood");
    m_ParticleManager->loadSystem("data/ParticleSystems/blood_explode.xml", "blood_explode");
    m_ParticleManager->loadSystem("data/ParticleSystems/wall_dust.xml", "wall_dust");
    m_ParticleManager->loadSystem("data/ParticleSystems/explosion_dust.xml", "explosion_dust");
    m_ParticleManager->loadSystem("data/ParticleSystems/smoke_dark.xml", "smoke_dark");
 
    m_Level->load("data/Levels/level1.xml");
 
    boost::shared_ptr<Player> player(new Player(this));
    m_PlayerId = m_EntityManager->add(player);
}
 
void World::update(float dt)
{
    m_Level->update(dt);
    m_EntityManager->update(dt);
    m_ParticleManager->update(dt);
}
 
void World::draw(sf::RenderTarget& target)
{
    //std::cout << "Drawing world" << std::endl;
 
    m_Level->draw(target);
 
    m_EntityManager->draw(target);
    m_ParticleManager->draw(target);
    m_LightManager->draw(target);
}
 
EntityManager* World::getEntityManager() const
{
    return m_EntityManager;
}
 
LightManager* World::getLightManager() const
{
    return m_LightManager;
}
 
ParticleManager* World::getParticleManager() const
{
    return m_ParticleManager;
}
 
Level* World::getLevel() const
{
    return m_Level;
}
 
int World::getPlayerId() const
{
    return m_PlayerId;
}
 
