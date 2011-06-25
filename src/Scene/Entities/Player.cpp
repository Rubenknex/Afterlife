#include "Player.h"

#include "Projectile.h"
#include "../Scene.h"
#include "../../Game.h"

Player::Player(Scene* scene, const std::string& id, const sf::Vector2f& pos) : 
    Entity(scene, id),
    m_flashLight(new SpotLight("flashlight", sf::Vector2f(0.0f, 0.0f), 1.0f, 300.0f, sf::Color(255, 230, 230), 0.0f, 15.0f))
{
    setType(Entity::PLAYER);
    setDrawLayer(3);
    
    m_sprite.SetImage(*IM.GetResource("data/Images/player_gun.png"));
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
    fixtureDef.filter.categoryBits = Entity::PLAYER;
    fixtureDef.filter.maskBits = Entity::OBJECT | Entity::ZOMBIE;
    
    m_body->CreateFixture(&fixtureDef);
    
    m_scene->addLight(m_flashLight);
    
    m_gunDef.load("data/Weapons/ak47.json");
    m_gun = new Gun(m_scene, &m_gunDef, this);
}

Player::~Player()
{
    std::cout << "Player Destructor!" << std::endl;
}

void Player::update(float dt)
{
    sf::Vector2f movement;
    if (g_input.isKeyDown(sf::Key::A))
        movement.x -= 1.0f;
    if (g_input.isKeyDown(sf::Key::D))
        movement.x += 1.0f;
    if (g_input.isKeyDown(sf::Key::W))
        movement.y -= 1.0f;
    if (g_input.isKeyDown(sf::Key::S))
        movement.y += 1.0f;
    
    if (movement.x != 0.0f || movement.y != 0.0f)
    {
        movement = math::normalize(movement);
        
        movement *= 4.0f;
        
        m_body->SetLinearVelocity(b2Vec2(movement.x, movement.y));
    }
    else
    {
        m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
    
    if (g_input.isMouseButtonDown(sf::Mouse::Left))
    {
        m_gun->shoot();
    }
    
    if (g_input.isKeyFirstDown(sf::Key::R))
    {
        m_gun->reload();
    }
    
    sf::Vector2f mousePos(g_input.getMouseX(), g_input.getMouseY());
    sf::Vector2f screenPos = g_Window->ConvertCoords(mousePos.x, mousePos.y);
    float rotation = atan2(screenPos.y - m_sprite.GetPosition().y, screenPos.x - m_sprite.GetPosition().x);
    m_body->SetTransform(m_body->GetPosition(), rotation);
    m_sprite.SetRotation(math::degrees(rotation) - 90.0f);
    
    sf::Vector2f newCenter = math::lerp(g_Window->GetView().GetCenter(), getPosition(), 0.05f);
    sf::View newView(newCenter, g_Window->GetView().GetSize());
    g_Window->SetView(newView);
    
    m_flashLight->setPosition(getPosition());
    m_flashLight->setAngle(m_sprite.GetRotation() + 90.0f);
    
    m_gun->update(dt);
}

void Player::draw(sf::RenderTarget& target)
{
    b2Vec2 pos = m_body->GetPosition();
    m_sprite.SetPosition(pos.x * m_scene->getMeterPixelRatio(), pos.y * m_scene->getMeterPixelRatio());
    
    target.Draw(m_sprite);
    
    m_gun->draw(target);
}

void Player::handleBeginContact(Entity* entity)
{
    
}

void Player::handleEndContact(Entity* entity)
{
    
}
