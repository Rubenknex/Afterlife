#ifndef PARTICLEMANAGER_H_INCLUDED
#define PARTICLEMANAGER_H_INCLUDED
 
#include <SFML/Graphics.hpp>
#include <vector>
 
#include "ParticleSystem.h"
 
using boost::shared_ptr;
 
class ParticleManager
{
public:
    ParticleManager();
    ~ParticleManager();
 
    void loadSystem(const std::string& filename, const std::string& name);
    void fireSystem(const std::string& name, sf::Vector2f pos);
 
    void update(float dt);
    void draw(sf::RenderTarget& target);
 
private:
    std::vector<ParticleSystem> mParticleSystems;
};
 
#endif // PARTICLEMANAGER_H_INCLUDED
 
