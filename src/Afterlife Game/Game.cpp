#include "Game.h"

#include "Scripting/ScriptManager.h"

namespace al
{
    sf::RenderWindow* g_Window;

    Game::Game()
    {

    }

    Game::~Game()
    {

    }

    void Game::initialize()
    {
        m_Window.Create(sf::VideoMode(1280, 720, 32), "Afterlife");
        m_Window.SetFramerateLimit(60);
        m_Window.EnableVerticalSync(true);

        g_Window = &m_Window;

        boost::shared_ptr<PlayState> playState(new PlayState(&m_Window));
        pushState(playState);
    }

    void Game::update()
    {
        float dt = m_Clock.GetElapsedTime();
        m_Framerate = 1.0f / dt;
        m_Clock.Reset();

        g_Input.update(m_Window.GetInput());

        if (m_States.size() > 0)
            m_States.front()->update(dt);
    }

    void Game::draw()
    {
        m_Window.Clear();

        if (m_States.size() > 0)
            m_States.front()->draw(m_Window);

        m_Window.Display();
    }

    void Game::run()
    {
        initialize();

        while (m_Window.IsOpened())
        {
            sf::Event event;

            while (m_Window.PollEvent(event))
            {
                if (event.Type == sf::Event::Closed)
                    m_Window.Close();
            }

            update();

            draw();
        }
    }

    void Game::pushState(StatePtr state)
    {
        m_States.push(state);
    }

    void Game::popState()
    {
        m_States.pop();
    }
}
