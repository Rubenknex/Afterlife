#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED
 
#include <boost/lexical_cast.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <string>
 
#include "TinyXML/tinyxml.h"
 
#include "../Parsing.h"
#include "../ResourceManager.h"
 
struct Particle
{
    sf::Vector2f pos;
    sf::Vector2f vel;
    float scale;
    float rotation;
    float timeAlive;
    float lifeSpan;
    bool alive;
};
 
class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();
 
    void load(const std::string& filename);
    
    void fire(sf::Vector2f pos);
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    const std::string& getName() const;
    
    bool operator<(const ParticleSystem& rhs) const;
 
private:
    std::string m_name;
    
    sf::Sprite m_texture;
    
    int m_drawOrder;
    
    sf::Color m_color;
    float m_minSpeed, m_maxSpeed;
    float m_minAngle, m_maxAngle;
    float m_minScale, m_maxScale;
    float m_minRotation, m_maxRotation;
    float m_minLifeSpan, m_maxLifeSpan;
    int m_minParticles, m_maxParticles;
    
    const static int MAX_PARTICLES = 100;
    Particle m_particles[MAX_PARTICLES];
};
 
#endif // PARTICLESYSTEM_H_INCLUDED
 
