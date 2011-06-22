#include "Projectile.h"

#include "Zombie.h"
#include "../Scene.h"

Projectile::Projectile(Scene* scene, const std::string& id, const sf::Vector2f& pos, float direction, float speed, float damage) :
    Entity(scene, id),
    m_damage(damage),
    m_lifeTime(5.0f),
    m_lifeTimeTimer(0.0f)
{
    setType("projectile");
    setDrawLayer(4);
    
    m_velocity = b2Vec2(cos(math::radians(direction)), sin(math::radians(direction)));
    m_velocity *= speed;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x / m_scene->getMeterPixelRatio(), pos.y / m_scene->getMeterPixelRatio());
    bodyDef.bullet = true;
    bodyDef.userData = this;
    
    m_body = m_scene->getB2World()->CreateBody(&bodyDef);
    
    b2CircleShape shape;
    shape.m_radius = 1.0f / m_scene->getMeterPixelRatio();
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = 0.0f;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.filter.categoryBits = Entity::PROJECTILE;
    fixtureDef.filter.maskBits = Entity::OBJECT | Entity::ZOMBIE;
    
    m_body->CreateFixture(&fixtureDef);
}

Projectile::~Projectile()
{
    
}

void Projectile::update(float dt)
{
    m_body->SetLinearVelocity(m_velocity);
    
    m_lifeTimeTimer += dt;
    if (m_lifeTimeTimer >= m_lifeTime)
    {
        m_scene->scheduleEntityForRemoval(this);
    }
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
        Zombie* zombie = static_cast<Zombie*>(entity);
        
        zombie->inflictDamage(m_damage);
        
        m_scene->scheduleEntityForRemoval(this);
    }
}
