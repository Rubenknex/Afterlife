#include "Grenade.h"

#include "../Scene.h"

Grenade::Grenade(Scene* scene, const std::string& id, const sf::Vector2f& pos, float direction, float speed, float detonationTime) : 
    Entity(scene, id),
    m_detonationTime(detonationTime),
    m_detonationTimer(0.0f)
{
    setType("grenade");
    setDrawLayer(4);
    
    m_sprite.SetImage(*IM.GetResource("data/Images/grenade.png"));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    m_sprite.SetPosition(pos);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x / m_scene->getMeterPixelRatio(), pos.y / m_scene->getMeterPixelRatio());
    bodyDef.linearDamping = 0.5f;
    bodyDef.angularDamping = 0.3f;
    bodyDef.userData = this;
    
    m_body = m_scene->getB2World()->CreateBody(&bodyDef);
    
    b2CircleShape shape;
    shape.m_radius = 2.0f / m_scene->getMeterPixelRatio();
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.3f;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.8f;
    fixtureDef.filter.categoryBits = Entity::GRENADE;
    fixtureDef.filter.maskBits = Entity::OBJECT;
    
    m_body->CreateFixture(&fixtureDef);
    
    b2Vec2 velocity(cos(math::radians(direction)), sin(math::radians(direction)));
    velocity *= speed;
    m_body->ApplyForce(velocity, m_body->GetPosition());
}

Grenade::~Grenade()
{
    
}

void Grenade::update(float dt)
{
    m_detonationTimer += dt;
    if (m_detonationTimer >= m_detonationTime)
    {
        
        
        m_scene->scheduleEntityForRemoval(this);
    }
}

void Grenade::draw(sf::RenderTarget& target)
{
    target.Draw(m_sprite);
}

void Grenade::handleBeginContact(Entity* entity)
{
    std::string type = entity->getType();
}
