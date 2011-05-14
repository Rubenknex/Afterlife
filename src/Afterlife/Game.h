#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "InputState.h"
#include "PlayState.h"
#include "StateManager.h"

namespace al
{
    class StateManager;

    class Game
    {
        public:
            Game();
            ~Game();

            void initialize();
            void update();
            void draw();
            void run();

        private:
            sf::RenderWindow m_Window;
            sf::Clock m_Clock;

            float m_Framerate;
            StateManager m_StateManager;
    };

    extern sf::RenderWindow* g_Window;
}

#endif // GAME_H_INCLUDED
