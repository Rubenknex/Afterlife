#include "Decal.h"

#include "../Scene.h"

Decal::Decal(Scene* scene, const std::string& id, const sf::Vector2f& pos, float rotation, const std::string& decalFile, float fadingTime) : 
    Entity(scene, id),
    m_fadingTime(fadingTime),
    m_fadingTimer(0.0f)
{
    setType(Entity::DECAL);
    setDrawLayer(2);
    
    m_sprite.SetImage(*IM.GetResource(decalFile));
    m_sprite.SetSubRect(sf::IntRect(0, 0, 45, 60));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    m_sprite.SetPosition(pos);
    m_sprite.SetRotation(rotation);
}

Decal::~Decal()
{
    
}

void Decal::update(float dt)
{
    m_fadingTimer += dt;
    if (m_fadingTimer >= m_fadingTime)
    {
        m_scene->scheduleEntityForRemoval(this);
    }
    
    sf::Color color = m_sprite.GetColor();
    color.a = 255 - ((m_fadingTimer / m_fadingTime) * 255);
    m_sprite.SetColor(color);
}

void Decal::draw(sf::RenderTarget& target)
{
    target.Draw(m_sprite);
}
