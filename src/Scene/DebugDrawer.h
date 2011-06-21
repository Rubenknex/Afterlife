#ifndef DEBUGDRAWER_H_INCLUDED
#define DEBUGDRAWER_H_INCLUDED

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class DebugDrawer : public b2DebugDraw
{
    public:
        DebugDrawer(sf::RenderTarget* target, float drawScale, float lineThickness, float fillAlpha);
        ~DebugDrawer();
        
        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
        void DrawTransform(const b2Transform& xf);
        
        void setDrawScale(float scale);
        void setLineThickness(float thickness);
        void setFillAlpha(int fillAlpha);
    
    private:
        sf::RenderTarget* m_target;
        
        float m_drawScale;
        float m_lineThickness;
        float m_fillAlpha;
};

#endif // DEBUGDRAWER_H_INCLUDED
