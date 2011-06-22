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
    enum EntityType
    {
        DECAL = (1 << 0),
        GRENADE = (1 << 1),
        OBJECT = (1 << 2),
        PLAYER = (1 << 3),
        PROJECTILE = (1 << 4),
        ZOMBIE = (1 << 5),
    };

public:
    Entity(Scene* scene, const std::string& id);
    virtual ~Entity();
    
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget& target);
    
    virtual void handleBeginContact(Entity* entity);
    virtual void handleEndContact(Entity* entity);
    
    const std::string& getId() const;
    
    EntityType getType() const;
    void setType(EntityType type);
    
    bool receivesLight() const;
    void setReceivesLight(bool receiveLight);
    
    int getDrawLayer() const;
    void setDrawLayer(int drawLayer);
    
    const sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    
    float getRotation() const;
    void setRotation(float rotation);
    
    b2Body* getBody() const;
    
    bool hasPhysics() const;
    bool hasScripting() const;
    
    bool operator<(const Entity& rhs) const;
    
protected:
    Scene* m_scene;
    
    std::string m_id;
    EntityType m_type;
    
    bool m_receiveLight;
    
    int m_drawLayer;
    sf::Sprite m_sprite;

    b2Body* m_body;

    Script* m_script;
};

#endif // ENTITY_H_INCLUDED
