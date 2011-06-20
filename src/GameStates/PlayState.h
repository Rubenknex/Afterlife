#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED
 
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
 
#include "IGameState.h"
#include "../InputState.h"
#include "../Scripting/Script.h"
#include "../UI.h"
 
using boost::shared_ptr;
 
class EntityManager;
class ParticleManager;
class Player;
class ProjectileManager;
class Weapon;
class World;
class Zombie;
 
class PlayState : public IGameState
{
public:
    PlayState(sf::RenderWindow* window);
    ~PlayState();
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
    sf::RenderWindow* getWindow();
 
private:
    sf::RenderWindow* mWindow;
    UI* m_UI;
 
    World* m_World;
};
 
#endif // PLAYSTATE_H_INCLUDED
 
