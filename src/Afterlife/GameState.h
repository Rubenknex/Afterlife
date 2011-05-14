#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "StateManager.h"

namespace al
{
    class StateManager;

    class GameState
    {
        public:
            GameState();
            ~GameState();

            virtual void update(float dt);
            virtual void draw(sf::RenderTarget& target);

            void setManager(StateManager* manager);

        private:
            StateManager* mManager;
    };
}

#endif // GAMESTATE_H_INCLUDED
