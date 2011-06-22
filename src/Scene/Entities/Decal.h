#ifndef DECAL_H_INCLUDED
#define DECAL_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../../ResourceManager.h"

class Scene;

class Decal : public Entity
{
public:
    Decal(Scene* scene, const std::string& id, const sf::Vector2f& pos, float rotation, const std::string& decalFile, float fadingTime);
    ~Decal();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);

private:
    float m_fadingTime;
    float m_fadingTimer;
};

#endif // DECAL_H_INCLUDED
