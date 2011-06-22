#ifndef GRENADE_H_INCLUDED
#define GRENADE_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../../Math.h"
#include "../../ResourceManager.h"

class Scene;

class Grenade : public Entity
{
public:
    Grenade(Scene* scene, const std::string& id, const sf::Vector2f& pos, float direction, float speed, float detonationTime);
    ~Grenade();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void handleBeginContact(Entity* entity);

private:
    float m_detonationTime;
    float m_detonationTimer;
};

#endif // GRENADE_H_INCLUDED
