#ifndef TESTSTATE_H_INCLUDED
#define TESTSTATE_H_INCLUDED

#include <boost/shared_ptr.hpp>

#include "IGameState.h"
#include "../Scene/Scene.h"
#include "../Scene/Entities/Player.h"
#include "../Scene/Entities/Zombie.h"
#include "../Scripting/ScriptManager.h"
#include "../InputState.h"

class TestState : public IGameState
{
public:
    TestState();
    ~TestState();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
private:
    Scene* m_scene;
    
    Entity* m_player;
};

#endif // TESTSTATE_H_INCLUDED
