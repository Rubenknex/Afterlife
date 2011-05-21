#include "StateManager.h"

#include "Game.h"

namespace al
{
    StateManager::StateManager(Game* game) :
        m_Game(game)
    {

    }

    StateManager::~StateManager()
    {
        while (mStates.size() > 0)
        {
            delete mStates.front();
            mStates.pop();
        }
    }

    void StateManager::update(float dt)
    {
        if (mStates.size() > 0)
            mStates.front()->update(dt);
    }

    void StateManager::draw(sf::RenderWindow& window)
    {
        //std::cout << "Drawing StateManager" << std::endl;

        if (mStates.size() > 0)
            mStates.front()->draw(window);
    }

    void StateManager::pushState(GameState* state)
    {
        state->setManager(this);
        mStates.push(state);
    }

    void StateManager::popState()
    {
        delete mStates.front();
        mStates.pop();
    }
}
