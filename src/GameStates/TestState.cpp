#include "TestState.h"

TestState::TestState()
{
    m_scene = new Scene();
    m_scene->load("data/Scenes/scene1.json");
    
    m_player = EntityPtr(new Player(m_scene, "player"));
    m_scene->addEntity(m_player);
}

TestState::~TestState()
{
    delete m_scene;
}

void TestState::update(float dt)
{
    m_scene->update(dt);
}

void TestState::draw(sf::RenderTarget& target)
{
    m_scene->draw(target);
}
