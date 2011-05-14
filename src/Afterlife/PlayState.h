#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "GameState.h"
#include "InputState.h"
#include "UI.h"
//#include "World.h"

using boost::shared_ptr;

namespace al
{
    class EntityManager;
    class ParticleManager;
    class Player;
    class ProjectileManager;
    class Weapon;
    class World;
    class Zombie;

    class PlayState : public GameState
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
}

#endif // PLAYSTATE_H_INCLUDED
