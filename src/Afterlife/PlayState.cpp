#include "PlayState.h"

#include "Scripting/ScriptInterface.h"
#include "World.h"

namespace al
{
    PlayState::PlayState(sf::RenderWindow* window) :
        mWindow(window),
        m_World(new World()),
        m_UI(new UI(m_World))
    {
        setWorld(m_World);
    }

    PlayState::~PlayState()
    {
        delete m_World;
    }

    void PlayState::update(float dt)
    {
        //std::cout << "Updating Playstate" << std::endl;
        m_World->update(dt);

        m_UI->update(dt);
    }

    void PlayState::draw(sf::RenderTarget& target)
    {
        //std::cout << "Drawing Playstate" << std::endl;
        m_World->draw(target);

        m_UI->draw(target);
    }

    sf::RenderWindow* PlayState::getWindow()
    {
        return mWindow;
    }
}
