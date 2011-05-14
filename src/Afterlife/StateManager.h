#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

//#include <boost/shared_ptr.hpp>
#include <queue>

#include "GameState.h"

namespace al
{
    class Game;
    class GameState;

    /// Manages the gamestates like the menu, game and pause menu.
    class StateManager
    {
        public:
            StateManager(Game* game);
            ~StateManager();

            void update(float dt);
            void draw(sf::RenderWindow& window);

            /// Push a state on top of the other states, the state on top of the stack gets updated and drawn.
            void pushState(GameState* state);
            /// Pop a state off the stack.
            void popState();

        private:
            Game* m_Game;

            std::queue<GameState*> mStates;
    };
}

#endif // STATEMANAGER_H_INCLUDED
