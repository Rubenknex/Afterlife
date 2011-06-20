#include "DebugDrawer.h"

#include <iostream>

DebugDrawer::DebugDrawer(sf::RenderTarget* target, float drawScale, float lineThickness, float fillAlpha) : 
    b2DebugDraw(),
    m_target(target),
    m_drawScale(drawScale),
    m_lineThickness(lineThickness),
    m_fillAlpha(fillAlpha)
{
    
}

DebugDrawer::~DebugDrawer()
{
    
}

void DebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::Color outlineColor(color.r * 255, color.g * 255, color.b * 255);
    
    sf::Shape polygon;
    
    for (int i = 0; i < vertexCount; i++)
    {
        polygon.AddPoint(vertices[i].x * m_drawScale, vertices[i].y * m_drawScale, sf::Color::White, outlineColor);
    }
    
    polygon.EnableFill(false);
    polygon.EnableOutline(true);
    polygon.SetOutlineThickness(m_lineThickness);
    
    m_target->Draw(polygon);
}

void DebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    sf::Color insideColor(color.r * 255, color.g * 255, color.b * 255, m_fillAlpha * 255);
    sf::Color outlineColor(color.r * 255, color.g * 255, color.b * 255);
    
    if (vertexCount > 2)
    {
        sf::Shape polygon;
        
        for (int i = 0; i < vertexCount; i++)
        {
            polygon.AddPoint(vertices[i].x * m_drawScale, vertices[i].y * m_drawScale, insideColor, outlineColor);
        }
        
        polygon.EnableOutline(true);
        polygon.SetOutlineThickness(m_lineThickness);
        
        m_target->Draw(polygon);
    }
    else
    {
        sf::Shape line = sf::Shape::Line(vertices[0].x * m_drawScale, vertices[0].y * m_drawScale, vertices[1].x * m_drawScale, vertices[1].y * m_drawScale, m_lineThickness, outlineColor);
        
        m_target->Draw(line);
    }
}

void DebugDrawer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    sf::Color insideColor(color.r * 255, color.g * 255, color.b * 255, m_fillAlpha * 255);
    sf::Color outlineColor(color.r * 255, color.g * 255, color.b * 255);
    
    sf::Shape solidCircle = sf::Shape::Circle(center.x * m_drawScale, center.y * m_drawScale, radius * m_drawScale, insideColor, m_lineThickness, outlineColor);
    
    solidCircle.EnableFill(false);
    
    m_target->Draw(solidCircle);
}

void DebugDrawer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    sf::Color insideColor(color.r * 255, color.g * 255, color.b * 255, m_fillAlpha * 255);
    sf::Color outlineColor(color.r * 255, color.g * 255, color.b * 255);
    
    sf::Shape solidCircle = sf::Shape::Circle(center.x * m_drawScale, center.y * m_drawScale, radius * m_drawScale, insideColor, m_lineThickness, outlineColor);
    
    m_target->Draw(solidCircle);
}

void DebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    sf::Color lineColor(color.r * 255, color.g * 255, color.b * 255);
    
    sf::Shape segment = sf::Shape::Line(p1.x * m_drawScale, p1.y * m_drawScale, p2.x * m_drawScale, p2.y * m_drawScale, m_lineThickness, sf::Color::White);
    
    m_target->Draw(segment);
    
    sf::Shape line = sf::Shape::Line(0.0f, 0.0f, 100.0f, 100.0f, 1.0f, sf::Color::White);
    m_target->Draw(line);
    
    std::cout << "Drawing a segment" << std::endl;
}

void DebugDrawer::DrawTransform(const b2Transform& xf)
{
    
}

void DebugDrawer::setDrawScale(float scale)
{
    m_drawScale = scale;
}
