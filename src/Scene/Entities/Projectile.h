#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <Box2D/Box2D.h>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../../Math.h"

class Projectile : public Entity
{
public:
    Projectile(Scene* scene, const std::string& id, const sf::Vector2f& pos, float direction, float speed, float damage);
    ~Projectile();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void handleBeginContact(Entity* entity);

private:
    b2Vec2 m_velocity;

    sf::Shape m_line;

    float m_damage;
    
    float m_lifeTime;
    float m_lifeTimeTimer;
};

#endif // PROJECTILE_H_INCLUDED
