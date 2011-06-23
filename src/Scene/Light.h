#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
 
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
 
#include "../Functions.h"
 
/// Represents a light.
class Light
{
public:
    enum LightType
    {
        LT_POINT,
        LT_SPOT,
    };
    
public:
    Light(const std::string& id, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color);
    ~Light();
 
    void draw(sf::RenderTarget* target);
 
    const std::string& getId() const;
    
    LightType getType() const;
    void setType(LightType type);
 
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    
    float getIntensity() const;
    void setIntensity(float intensity);
    
    float getRadius() const;
    void setRadius(float radius);
    
    const sf::Color& getColor() const;
    void setColor(const sf::Color& color);
    
    void setOn(bool on);
 
protected:
    /// Generate the vertices which represent the light.
    virtual void generateVertices() = 0;
    /// Adds a triangle (sf::Shape) to our vector of shapes.
    void addTriangle(const sf::Vector2f v1, const sf::Vector2f v2);
 
protected:
    std::string m_id;
    LightType m_type;
    
    bool m_on;
    sf::Vector2f m_position;
    float m_intensity;
    float m_radius;
    sf::Color m_color;
 
    std::vector<sf::Shape> m_triangles;
};
 
#endif // LIGHT_H_INCLUDED
 
