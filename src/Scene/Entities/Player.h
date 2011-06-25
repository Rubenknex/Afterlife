#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <Box2D/Box2D.h>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "../SpotLight.h"
#include "../../Gun.h"
#include "../../InputState.h"
#include "../../Math.h"
#include "../../ResourceManager.h"

class Player : public Entity
{
public:
    Player(Scene* scene, const std::string& id, const sf::Vector2f& pos);
    ~Player();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void handleBeginContact(Entity* entity);
    void handleEndContact(Entity* entity);

private:
    SpotLight* m_flashLight;
    
    GunDef m_gunDef;
    Gun* m_gun;
};

#endif // PLAYER_H_INCLUDED
