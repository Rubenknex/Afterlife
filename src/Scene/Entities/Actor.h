#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../../Scripting/Script.h"
#include "../../Scripting/ScriptManager.h"

class Scene;

class Actor
{
public:
    Actor(Scene* scene);
    ~Actor();
    
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    
    std::string getId();
    std::string getType();

protected:
    Scene* m_scene;
    
    std::string m_id;
    std::string m_type;
    
    sf::Sprite m_sprite;
    
    bool m_usePhysics;
    b2Body* m_body;
    
    bool m_useScripting;
    Script* m_script;
};

#endif // ACTOR_H_INCLUDED
