#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
 
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <queue>
 
#include "InputState.h"
#include "GameStates/PlayState.h"
#include "GameStates/TestState.h"
 
class StateManager;
 
typedef boost::shared_ptr<IGameState> GameStatePtr;
 
class Game
{
public:
    Game();
    ~Game();
 
    void initialize();
    void update();
    void draw();
    void run();
 
    void pushState(GameStatePtr state);
    void popState();
 
private:
    sf::RenderWindow m_Window;
    sf::Clock m_Clock;
 
    float m_Framerate;
 
    std::queue<GameStatePtr> m_States;
};
 
extern sf::RenderWindow* g_Window;
 
#endif // GAME_H_INCLUDED
 
