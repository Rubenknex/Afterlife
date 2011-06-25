#ifndef POINTLIGHT_H_INCLUDED
#define POINTLIGHT_H_INCLUDED
 
#include "Light.h"
 
class PointLight : public Light
{
public:
    PointLight(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, int quality);
    ~PointLight();
    
    int getQuality() const;
    void setQuality(int quality);
 
private:
    void generateVertices();
 
private:
    int m_quality;
};
 
#endif // POINTLIGHT_H_INCLUDED
 
