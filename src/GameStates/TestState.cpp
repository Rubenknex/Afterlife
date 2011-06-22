#include "TestState.h"

#include "../Scripting/ScriptInterface.h"

TestState::TestState()
{
    m_scene = new Scene(true);
    
    setScriptingScene(m_scene);
    g_scriptManager.registerInterface(new ScriptInterface());
    
    m_scene->load("data/Scenes/scene1.json");
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
