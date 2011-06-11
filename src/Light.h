#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
 
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
 
#include "Functions.h"
 
/// Represents a light.
class Light
{
public:
    Light(const std::string& name, const sf::Vector2f& pos, float intensity, float radius, const sf::Color& color);
    ~Light();
 
    void draw(sf::RenderTarget* target);
 
    std::string getName();
 
    const sf::Vector2f& getPosition();
    void setPosition(const sf::Vector2f& pos);
    void setIntensity(float intensity);
    float getIntensity();
    float getRadius();
    void setRadius(float radius);
    void setOn(bool on);
 
protected:
    /// Generate the vertices which represent the light.
    virtual void generateVertices() = 0;
    /// Adds a triangle (sf::Shape) to our vector of shapes.
    void addTriangle(const sf::Vector2f v1, const sf::Vector2f v2);
 
protected:
    std::string m_Name;
    bool mOn;
    sf::Vector2f mPosition;
    float mIntensity;
    float mRadius;
    sf::Color mColor;
 
    std::vector<sf::Shape> mTriangles;
};
 
#endif // LIGHT_H_INCLUDED
 
