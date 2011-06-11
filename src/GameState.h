#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

namespace al
{
    class GameState
    {
        public:
            GameState();
            virtual ~GameState();

            virtual void update(float dt);
            virtual void draw(sf::RenderTarget& target);
    };
}

#endif // GAMESTATE_H_INCLUDED
