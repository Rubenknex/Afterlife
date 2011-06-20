#ifndef IGAMESTATE_H_INCLUDED
#define IGAMESTATE_H_INCLUDED
 
class IGameState
{
public:
    IGameState() { }
    virtual ~IGameState() { }
 
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
};
 
#endif // IGAMESTATE_H_INCLUDED
 
