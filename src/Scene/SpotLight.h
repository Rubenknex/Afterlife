#ifndef SPOTLIGHT_H_INCLUDED
#define SPOTLIGHT_H_INCLUDED
 
#include "Light.h"
 
class SpotLight : public Light
{
public:
    SpotLight(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, float angle, float openAngle);
    ~SpotLight();
 
    float getAngle() const;
    void setAngle(float angle);
    
    float getOpenAngle() const;
    void setOpenAngle(float openAngle);
 
private:
    void generateVertices();
 
private:
    float m_angle;
    float m_openAngle;
};
 
#endif // SPOTLIGHT_H_INCLUDED
 
