#include "SpotLight.h"
 
SpotLight::SpotLight(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color, float angle, float openAngle) :
    Light(id, pos, intensity, radius, color),
    m_angle(angle),
    m_openAngle(openAngle)
{
    generateVertices();
}
 
SpotLight::~SpotLight()
{
 
}

float SpotLight::getAngle() const
{
    return m_angle;
}
 
void SpotLight::setAngle(float angle)
{
    m_angle = angle;
 
    m_triangles[0].SetRotation(angle);
}
 
void SpotLight::generateVertices()
{
    m_triangles.clear();
 
    float angleRad = m_angle * M_PI / 180.0;
    float openAngleRad = m_openAngle * M_PI / 180.0;
 
    addTriangle(sf::Vector2f(m_radius * cos(angleRad - openAngleRad), m_radius * sin(angleRad - openAngleRad)),
                sf::Vector2f(m_radius * cos(angleRad + openAngleRad), m_radius * sin(angleRad + openAngleRad)));
}
 
