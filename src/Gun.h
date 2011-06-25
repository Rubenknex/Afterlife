#ifndef GUN_H_INCLUDED
#define GUN_H_INCLUDED

#include <fstream>
#include <json/json.h>

class Entity;
class PointLight;
class Projectile;
class Scene;

class GunDef
{
public:
    void load(const std::string& filename);
    
public:
    std::string m_name;
    
    std::string m_imageFile;
    std::string m_fireSoundFile;
    std::string m_reloadSoundFile;
    
    int m_clipCapacity;
    int m_roundPerMinute;
    
    float m_damage;
    float m_reloadTime;
};

class Gun
{
public:
    Gun(Scene* scene, GunDef* gunDef, Entity* owner);
    ~Gun();
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void shoot();
    void reload();
    
private:
    Scene* m_scene;

    GunDef* m_gunDef;
    
    Entity* m_owner;
    
    sf::Sprite m_sprite;
    
    PointLight* m_light;
    float m_lightFlashTime;
    float m_lightFlashTimer;
    bool m_justFired;
    
    float m_shootTimer;
    float m_reloadTimer;
    
    int m_totalBullets;
    int m_bulletsInClip;
    
    bool m_reloading;
};

#endif // GUN_H_INCLUDED
