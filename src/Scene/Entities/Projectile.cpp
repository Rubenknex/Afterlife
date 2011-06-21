#include "Projectile.h"

#include "../Scene.h"

Projectile::Projectile(Scene* scene, const std::string& id) :
    Entity(scene, id)
{
    
}

Projectile::~Projectile()
{
    
}

void Projectile::update(float dt)
{
    
}

void Projectile::draw(sf::RenderTarget& target)
{
    b2Vec2 bPos = m_body->GetPosition();
    sf::Vector2f position(bPos.x * m_scene->getMeterPixelRatio(), bPos.y * m_scene->getMeterPixelRatio());
    b2Vec2 bVel = m_body->GetLinearVelocity();
    sf::Vector2f direction = math::normalize(sf::Vector2f(bVel.x, bVel.y));
    
    m_line = sf::Shape::Line(position, position + direction * 5.0f, 1.0f, sf::Color::White);
    
    target.Draw(m_line);
}

void Projectile::handleBeginContact(Entity* entity)
{
    std::string type = entity->getType();
    
    if (type == "object")
    {
        m_scene->scheduleEntityForRemoval(this);
    }
    else if (type == "zombie")
    {
        // do damage to zombie
    }
}
