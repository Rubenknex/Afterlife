#include "TestState.h"

TestState::TestState()
{
    m_scene = new Scene();
    m_scene->load("data/Scenes/scene1.json");
    
    m_scene->loadParticleSystem("data/ParticleSystems/blood.json");
    m_scene->loadParticleSystem("data/ParticleSystems/smoke_dark.json");
    
    m_player = new Player(m_scene, "player");
    m_scene->addEntity(m_player);
    
    m_scene->addEntity(new Zombie(m_scene, "zombie_1", sf::Vector2f(300.0f, 300.0f)));
    m_scene->addEntity(new Zombie(m_scene, "zombie_2", sf::Vector2f(300.0f, 400.0f)));
    m_scene->addEntity(new Zombie(m_scene, "zombie_3", sf::Vector2f(400.0f, 300.0f)));
}

TestState::~TestState()
{
    delete m_scene;
}

void TestState::update(float dt)
{
    m_scene->update(dt);
    
    if (g_Input.isKeyFirstDown(sf::Key::Space))
        m_scene->scheduleEntityForRemoval(m_player);
}

void TestState::draw(sf::RenderTarget& target)
{
    m_scene->draw(target);
}
