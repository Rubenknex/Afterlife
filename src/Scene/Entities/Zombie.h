#ifndef ZOMBIE_H_INCLUDED
#define ZOMBIE_H_INCLUDED

#include <boost/lexical_cast.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../../Math.h"

class Zombie : public Entity
{
public:
    Zombie(Scene* scene, const std::string& id, const sf::Vector2f& pos);
    ~Zombie();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void handleBeginContact(Entity* entity);
    void handleEndContact(Entity* entity);
    
    void inflictDamage(float damage);

private:
    float m_health;
};

#endif // ZOMBIE_H_INCLUDED
