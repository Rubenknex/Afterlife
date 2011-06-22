#include "Zombie.h"

#include "Decal.h"
#include "../Scene.h"

Zombie::Zombie(Scene* scene, const std::string& id, const sf::Vector2f& pos) : 
    Entity(scene, id),
    m_health(100.0f)
{
    setType("zombie");
    
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
    fixtureDef.filter.categoryBits = Entity::ZOMBIE;
    fixtureDef.filter.maskBits = Entity::OBJECT | Entity::PLAYER | Entity::PROJECTILE | Entity::ZOMBIE;
    
    m_body->CreateFixture(&fixtureDef);
}

Zombie::~Zombie()
{
    
}

void Zombie::update(float dt)
{
    m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    
    if (m_health <= 0.0f)
    {
        b2Vec2 bPos = m_body->GetPosition();
        sf::Vector2f pos(bPos.x * m_scene->getMeterPixelRatio(), bPos.y * m_scene->getMeterPixelRatio());
        
        std::string decalFile = boost::str(boost::format("data/Images/Decals/blood_%1%.png") % sf::Randomizer::Random(1, 4));
        
        m_scene->addEntity(new Decal(m_scene, m_scene->getRandomId(), pos, sf::Randomizer::Random(0.0f, 360.0f), decalFile, sf::Randomizer::Random(10.0f, 15.0f)));
        
        m_scene->scheduleEntityForRemoval(this);
    }
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

void Zombie::inflictDamage(float damage)
{
    m_health -= damage;
}
