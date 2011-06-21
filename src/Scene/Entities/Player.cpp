#include "Player.h"

#include "../Scene.h"

Player::Player(Scene* scene, const std::string& id) : 
    Entity(scene, id)
{
    m_sprite.SetImage(*IM.GetResource("data/Images/player_gun.png"));
    m_sprite.SetSubRect(sf::IntRect(0, 0, 45, 60));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
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

Player::~Player()
{
    std::cout << "Player Destructor!" << std::endl;
}

void Player::update(float dt)
{
    sf::Vector2f movement;
    if (g_Input.isKeyDown(sf::Key::A))
        movement.x -= 1.0f;
    if (g_Input.isKeyDown(sf::Key::D))
        movement.x += 1.0f;
    if (g_Input.isKeyDown(sf::Key::W))
        movement.y -= 1.0f;
    if (g_Input.isKeyDown(sf::Key::S))
        movement.y += 1.0f;
    
    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        movement = math::normalize(movement);
        
        movement *= 3.0f;
        
        m_body->SetLinearVelocity(b2Vec2(movement.x, movement.y));
    }
    else
    {
        m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
    
    sf::Vector2f mousePos(g_Input.getMouseX(), g_Input.getMouseY());
    sf::Vector2f screenPos = g_Window->ConvertCoords(mousePos.x, mousePos.y);
    float rotation = atan2(screenPos.y - m_sprite.GetPosition().y, screenPos.x - m_sprite.GetPosition().x);
    m_sprite.SetRotation(math::degrees(rotation) - 90.0f);
    
    //m_body->SetTransform(m_body->GetPosition(), rotation);
}

void Player::draw(sf::RenderTarget& target)
{
    b2Vec2 pos = m_body->GetPosition();
    m_sprite.SetPosition(pos.x * m_scene->getMeterPixelRatio(), pos.y * m_scene->getMeterPixelRatio());
    
    target.Draw(m_sprite);
}

void Player::handleBeginContact(Entity* entity)
{
    
}

void Player::handleEndContact(Entity* entity)
{
    
}
