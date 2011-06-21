#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../../Scripting/Script.h"
#include "../../Scripting/ScriptManager.h"

class Scene;

class Entity
{
public:
    Entity(Scene* scene, const std::string& id);
    virtual ~Entity();
    
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target);
    
    virtual void handleBeginContact(Entity* entity);
    virtual void handleEndContact(Entity* entity);
    
    std::string getId();
    
    std::string getType();
    void setType(const std::string& type);
    
    bool hasPhysics();
    bool hasScripting();
    
protected:
    Scene* m_scene;
    
    std::string m_id;
    std::string m_type;
    
    sf::Sprite m_sprite;

    b2Body* m_body;

    Script* m_script;
};

#endif // ENTITY_H_INCLUDED
