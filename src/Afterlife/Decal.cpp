#include "Decal.h"

namespace al
{
    Decal::Decal(World* world, const sf::Image& img, const sf::Vector2f pos, float lifetime) :
        Entity(world),
        mLifetime(lifetime),
        mFadingTimer(0.0f)
    {
        SetImage(img);
        SetPosition(pos);
        SetRotation(sf::Randomizer::Random(0.0f, 360.0f));
        SetOrigin(GetSize() / 2.0f);
    }

    Decal::~Decal()
    {

    }

    void Decal::update(float dt)
    {
        mFadingTimer += dt;

        int alpha = 255 - ((mFadingTimer / mLifetime) * 255);
        SetColor(sf::Color(255, 255, 255, alpha));

        if (mFadingTimer >= mLifetime)
            setAlive(false);
    }

    void Decal::draw(sf::RenderWindow& window)
    {
        window.Draw(*this);
    }
}
