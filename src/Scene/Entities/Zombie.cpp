#include "Zombie.h"

#include "../Scene.h"

Zombie::Zombie(Scene* scene, const std::string& id, const sf::Vector2f& pos) : 
    Entity(scene, id)
{
    m_sprite.SetImage(*IM.GetResource("data/Images/zombie_1.png"));
    m_sprite.SetSubRect(sf::IntRect(0, 0, 45, 60));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x / m_scene->getMeterPixelRatio(), pos.y / m_scene->getMeterPixelRatio());
    bodyDef.userData = this;
    
    m_body = m_scene->getB2World()->CreateBody(&bodyDef);
    
    b2CircleShape shape;
    shape.m_radius = 24.0f / m_scene->getMeterPixelRatio();
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.3f;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.1f;
    
    m_body->CreateFixture(&fixtureDef);
}

Zombie::~Zombie()
{
    
}

void Zombie::update(float dt)
{
    m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Zombie::draw(sf::RenderTarget& target)
{
    b2Vec2 pos = m_body->GetPosition();
    m_sprite.SetPosition(pos.x * m_scene->getMeterPixelRatio(), pos.y * m_scene->getMeterPixelRatio());
    
    target.Draw(m_sprite);
}

void Zombie::handleBeginContact(Entity* entity)
{
    
}

void Zombie::handleEndContact(Entity* entity)
{
    
}
