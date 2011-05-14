#include "Game.h"

namespace al
{
    sf::RenderWindow* g_Window;

    Game::Game() :
        m_StateManager(this)
    {

    }

    Game::~Game() { }

    void Game::initialize()
    {
        m_Window.Create(sf::VideoMode(1280, 720, 32), "Afterlife");
        m_Window.SetFramerateLimit(60);
        m_Window.EnableVerticalSync(true);

        g_Window = &m_Window;

        m_StateManager.pushState(new PlayState(&m_Window));
    }

    void Game::update()
    {
        float dt = m_Clock.GetElapsedTime();
        m_Framerate = 1.0f / dt;
        m_Clock.Reset();

        g_Input.update(m_Window.GetInput());

        m_StateManager.update(dt);
    }

    void Game::draw()
    {
        m_Window.Clear();

        m_StateManager.draw(m_Window);

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
}
