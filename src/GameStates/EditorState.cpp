#include "EditorState.h"

EditorState::EditorState() :
    m_scene(new Scene(false)),
    m_gizmo(Gizmo(m_scene))
{
    m_scene->load("data/Scenes/scene1.json");
    
    m_scene->setLightingEnabled(false);
}

EditorState::~EditorState()
{
    delete m_scene;
}

void EditorState::update(float dt)
{
    m_scene->update(dt);
    
    m_gizmo.update(dt);
}

void EditorState::draw(sf::RenderTarget& target)
{
    m_scene->draw(target);
    
    m_gizmo.draw(target);
}
