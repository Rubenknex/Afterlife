#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../../Math.h"

class Projectile : public Entity
{
public:
    Projectile(Scene* scene, const std::string& id);
    ~Projectile();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void handleBeginContact(Entity* entity);

private:
    sf::Shape m_line;

    float m_damage;
};

#endif // PROJECTILE_H_INCLUDED
