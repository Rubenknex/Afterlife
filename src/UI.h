#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
 
#include <boost/format.hpp>
#include <SFML/Graphics.hpp>
#include <string>
 
#include "ResourceManager.h"
 
class World;
 
class UI
{
public:
    UI(World* world);
    ~UI();
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
private:
    World* m_World;
 
    sf::Font mFont;
 
    sf::Text mFramerate;
    sf::Text mWeaponAmmo;
};
 
#endif // UI_H_INCLUDED
 
