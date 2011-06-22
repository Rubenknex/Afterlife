#ifndef IGAMESTATE_H_INCLUDED
#define IGAMESTATE_H_INCLUDED
 
class Game;
 
class IGameState
{
public:
    IGameState() { }
    virtual ~IGameState() { }
    
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
    
    void setGame(Game* game)
    {
        m_game = game;
    }

private:
    Game* m_game;
};
 
#endif // IGAMESTATE_H_INCLUDED
 
