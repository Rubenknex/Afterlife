#include "PointLight.h"
 
PointLight::PointLight(const std::string& name, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, int quality) :
    Light(name, pos, intensity, radius, color),
    mQuality(quality)
{
    generateVertices();
}
 
PointLight::~PointLight()
{
 
}
 
void PointLight::generateVertices()
{
    mTriangles.clear();
 
    float step = (M_PI * 2.0) / (float)mQuality;
 
    for (int i = 0; i < mQuality; i++)
    {
        addTriangle(sf::Vector2f(mRadius * cos(i * step), mRadius * sin(i * step)),
                    sf::Vector2f(mRadius * cos((i + 1) * step), mRadius * sin((i + 1) * step)));
    }
}
 
