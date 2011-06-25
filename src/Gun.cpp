#include "Gun.h"

#include "AudioPlayer.h"
#include "ResourceManager.h"
#include "Scene/Entities/Entity.h"
#include "Scene/Entities/Projectile.h"
#include "Scene/PointLight.h"
#include "Scene/Scene.h"

void GunDef::load(const std::string& filename)
{
    std::ifstream in(filename.c_str());
    
    if (!in.is_open())
    {
        return;
    }
    
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(in, root))
    {
        return;
    }
    
    in.close();
    
    m_name = root["name"].asString();
    m_imageFile = root["image"].asString();
    m_fireSoundFile = root["fireSound"].asString();
    m_reloadSoundFile = root["reloadSound"].asString();
    
    m_clipCapacity = root["clipCapacity"].asInt();
    m_roundPerMinute = root["roundsPerMinute"].asInt();
    
    m_damage = root["damage"].asDouble();
    m_reloadTime = root["reloadTime"].asDouble();
}

Gun::Gun(Scene* scene, GunDef* gunDef, Entity* owner) :
    m_scene(scene),
    m_gunDef(gunDef),
    m_owner(owner),
    m_light(new PointLight(m_scene->getRandomId("gunLight"), sf::Vector2f(), 0.3f, 100.0f, sf::Color(255, 229, 151), 8)),
    m_lightFlashTime(0.05f),
    m_lightFlashTimer(0.0f),
    m_justFired(false),
    m_shootTimer(0.0f),
    m_reloadTimer(0.0f),
    m_totalBullets(0),
    m_bulletsInClip(0),
    m_reloading(false)
{
    m_sprite.SetImage(*IM.GetResource(m_gunDef->m_imageFile));
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    
    m_light->setOn(false);
    m_scene->addLight(m_light);
    
    // Testing code
    m_totalBullets = 20 * m_gunDef->m_clipCapacity;
    m_bulletsInClip = m_gunDef->m_clipCapacity;
}

Gun::~Gun()
{
    
}

void Gun::update(float dt)
{
    if (m_reloading)
    {
        if (m_reloadTimer <= m_gunDef->m_reloadTime)
        {
            m_reloadTimer += dt;
        }
        else
        {
            int bulletsToAdd = m_gunDef->m_clipCapacity - m_bulletsInClip;
            
            if (m_totalBullets > bulletsToAdd)
            {
                m_bulletsInClip += bulletsToAdd;
                m_totalBullets -= bulletsToAdd;
            }
            else
            {
                m_bulletsInClip += m_totalBullets;
                m_totalBullets = 0;
            }
            
            m_reloading = false;
            m_reloadTimer = 0.0f;
        }
    }
    else
    {
        if (m_shootTimer <= (60.0f / m_gunDef->m_roundPerMinute))
            m_shootTimer += dt;
    }
    
    if (m_justFired)
    {
        m_lightFlashTimer += dt;
        
        if (m_lightFlashTimer > m_lightFlashTime)
        {
            m_light->setOn(false);
            m_lightFlashTimer = 0.0f;
        }
    }
}

void Gun::draw(sf::RenderTarget& target)
{
    float rotRads = math::radians(m_owner->getRotation());
    sf::Vector2f dirNormal(cos(rotRads), sin(rotRads));
    
    m_sprite.SetPosition(m_owner->getPosition() + dirNormal * 14.0f);
    m_sprite.SetRotation(m_owner->getRotation() - 90.0f);
    
    m_light->setPosition(m_owner->getPosition() + dirNormal * 14.0f);
    
    target.Draw(m_sprite);
}

void Gun::shoot()
{
    if (m_shootTimer > (60.0f / m_gunDef->m_roundPerMinute))
    {
        if (m_bulletsInClip > 0)
        {
            float rotRads = math::radians(m_owner->getRotation());
            sf::Vector2f dirNormal(cos(rotRads), sin(rotRads));
            
            m_scene->addEntity(new Projectile(m_scene, m_scene->getRandomId("projectile"), m_owner->getPosition() + dirNormal * 20.0f, m_owner->getRotation(), 30.0f, m_gunDef->m_damage));
            
            m_bulletsInClip -= 1;
            m_shootTimer = 0.0f;
            
            m_lightFlashTimer = 0.0f;
            m_light->setOn(true);
            m_justFired = true;
            
            g_audioPlayer.playSound(m_gunDef->m_fireSoundFile);
        }
    }
}

void Gun::reload()
{
    if (!m_reloading && m_bulletsInClip < m_gunDef->m_clipCapacity && m_totalBullets > 0)
    {
        m_reloading = true;
        
        g_audioPlayer.playSound(m_gunDef->m_reloadSoundFile, 100.0f, 1.0f);
    }
}
