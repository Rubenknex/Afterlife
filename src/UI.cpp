#include "UI.h"
 
#include "World.h"
 
UI::UI(World* world) :
    m_World(world),
    mFont(*FM.GetResource("data/Fonts/FreeSans.ttf"))
{
    mFramerate.SetFont(mFont);
    mFramerate.SetPosition(5.0f, 5.0f);
    mFramerate.SetColor(sf::Color::White);
 
    mWeaponAmmo.SetFont(mFont);
}
 
UI::~UI()
{
 
}
 
void UI::update(float dt)
{
    int framerate = 1.0f / g_Window->GetFrameTime();
    std::string framerateText = (boost::format("FPS: %1%") % framerate).str();
    mFramerate.SetString(framerateText);
 
    boost::shared_ptr<Player> player = boost::static_pointer_cast<Player>(m_World->getEntityManager()->getById(m_World->getPlayerId()));
    std::string weaponAmmo = (boost::format("%1% / %2%") % player->getWeapon()->getBulletsInMag() % player->getWeapon()->getBullets()).str();
    mWeaponAmmo.SetString(weaponAmmo);
}
 
void UI::draw(sf::RenderTarget& target)
{
    sf::View gameView(target.GetView().GetCenter(), target.GetView().GetSize());
 
    sf::View uiView(gameView.GetSize() / 2.0f, gameView.GetSize());
    target.SetView(uiView);
 
    target.Draw(mFramerate);
 
    mWeaponAmmo.SetColor(sf::Color::Black);
    mWeaponAmmo.SetPosition(1101.0f, 681.0f);
    target.Draw(mWeaponAmmo);
 
    mWeaponAmmo.SetColor(sf::Color::White);
    mWeaponAmmo.SetPosition(1100.0f, 680.0f);
    target.Draw(mWeaponAmmo);
 
    target.SetView(gameView);
 
}
 
