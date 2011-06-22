#include "PointLight.h"
 
PointLight::PointLight(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, int quality) :
    Light(id, pos, intensity, radius, color),
    m_quality(quality)
{
    generateVertices();
}
 
PointLight::~PointLight()
{
 
}
 
void PointLight::generateVertices()
{
    m_triangles.clear();
 
    float step = (M_PI * 2.0) / (float)m_quality;
 
    for (int i = 0; i < m_quality; i++)
    {
        addTriangle(sf::Vector2f(m_radius * cos(i * step), m_radius * sin(i * step)),
                    sf::Vector2f(m_radius * cos((i + 1) * step), m_radius * sin((i + 1) * step)));
    }
}
 
