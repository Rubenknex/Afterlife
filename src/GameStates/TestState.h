#ifndef TESTSTATE_H_INCLUDED
#define TESTSTATE_H_INCLUDED

#include "IGameState.h"
#include "../InputState.h"
#include "../Scene/Entities/Player.h"
#include "../Scene/Entities/Zombie.h"
#include "../Scene/Scene.h"
#include "../Scripting/ScriptManager.h"

class TestState : public IGameState
{
public:
    TestState();
    ~TestState();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
private:
    Scene* m_scene;
};

#endif // TESTSTATE_H_INCLUDED
