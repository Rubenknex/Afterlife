#ifndef EDITORSTATE_H_INCLUDED
#define EDITORSTATE_H_INCLUDED

#include "IGameState.h"
#include "../Editor/Gizmo.h"
#include "../InputState.h"
#include "../Scene/Entities/Player.h"
#include "../Scene/Entities/Zombie.h"
#include "../Scene/Scene.h"
#include "../Scripting/ScriptManager.h"

class EditorState : public IGameState
{
public:
    EditorState();
    ~EditorState();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
private:
    Scene* m_scene;
    
    Gizmo m_gizmo;
    
    sf::Text m_editorMode;
    sf::Text m_gizmoMode;
};

#endif // EDITORSTATE_H_INCLUDED
