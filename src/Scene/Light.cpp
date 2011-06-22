#include "Light.h"
 
Light::Light(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color) :
    m_id(id),
    m_on(true),
    m_position(pos),
    m_intensity(intensity),
    m_radius(radius),
    m_color(color)
{
 
}
 
Light::~Light()
{
 
}
 
void Light::draw(sf::RenderTarget* target)
{
    if (m_on)
    {
        for (int i = 0; i < (int)m_triangles.size(); i++)
        {
            target->Draw(m_triangles[i]);
        }
    }
}
 
const std::string& Light::getId() const
{
    return m_id;
}
 
const sf::Vector2f& Light::getPosition() const
{
    return m_position;
}
 
void Light::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;
 
    for (int i = 0; i < (int)m_triangles.size(); i++)
    {
        m_triangles[i].SetPosition(pos);
    }
}
 
float Light::getIntensity() const
{
    return m_intensity;
}

void Light::setIntensity(float intensity)
{
    m_intensity = intensity;
 
    for (int i = 0; i < (int)m_triangles.size(); i++)
    {
        m_triangles[i].SetPointColor(0, sf::Color((int)(m_intensity * m_color.r), (int)(m_intensity * m_color.g), (int)(m_intensity * m_color.b)));
    }
}

float Light::getRadius() const
{
    return m_radius;
}
 
void Light::setRadius(float radius)
{
    m_radius = radius;
 
    generateVertices();
}
 
void Light::setOn(bool on)
{
    m_on = on;
}
 
void Light::addTriangle(const sf::Vector2f v1, const sf::Vector2f v2)
{
    sf::Shape triangle;
 
    triangle.AddPoint(0.0f, 0.0f, sf::Color((int)(m_intensity * m_color.r), (int)(m_intensity * m_color.g), (int)(m_intensity * m_color.b)), sf::Color(255, 255, 255));
 
    triangle.AddPoint(v1, sf::Color(0, 0, 0), sf::Color(255, 255, 255));
    triangle.AddPoint(v2, sf::Color(0, 0, 0), sf::Color(255, 255, 255));
 
    triangle.SetBlendMode(sf::Blend::Add);
    triangle.SetPosition(m_position);
 
    m_triangles.push_back(triangle);
}
 
