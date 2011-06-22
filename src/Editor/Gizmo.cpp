#include "Gizmo.h"

#include "../Game.h"
#include "../InputState.h"
#include "../Scene/Entities/Entity.h"
#include "../Scene/Entities/Object.h"
#include "../Scene/Scene.h"

Gizmo::Gizmo(Scene* scene) :
    m_currentScene(scene),
    m_mode(Gizmo::MOVE),
    m_movingFree(false),
    m_movingHorizontally(false),
    m_movingVertically(false),
    m_selectedObject(NULL)
{
    m_triangleUp.AddPoint(-5.0f, -48.0f, sf::Color::Blue);
    m_triangleUp.AddPoint(0.0f, -58.0f, sf::Color::Blue);
    m_triangleUp.AddPoint(5.0f, -48.0f, sf::Color::Blue);
    
    m_triangleRight.AddPoint(48.0f, -5.0f, sf::Color::Red);
    m_triangleRight.AddPoint(58.0f, 0.0f, sf::Color::Red);
    m_triangleRight.AddPoint(48.0f, 5.0f, sf::Color::Red);
    
    m_lineUp = sf::Shape::Line(0.0f, 0.0f, 0.0f, -50.0f, 1.0f, sf::Color::Blue);
    m_lineRight = sf::Shape::Line(0.0f, 0.0f, 50.0f, 0.0f, 1.0f, sf::Color::Red);
    m_lineRotate = sf::Shape::Line(0.0f, 0.0f, 50.0f, 0.0f, 1.0f, sf::Color::Blue);
    m_lineScaleBlue = sf::Shape::Line(0.0f, 0.0f, 0.0f, -50.0f, 1.0f, sf::Color::Blue);
    m_lineScaleRed = sf::Shape::Line(0.0f, 0.0f, 50.0f, 0.0f, 1.0f, sf::Color::Red);
    
    m_rectangleCenter = sf::Shape::Rectangle(0.0f, -16.0f, 15.0f, 15.0f, sf::Color::Yellow, 1.0f, sf::Color::Yellow);
    m_rectangleCenter.EnableFill(false);
    m_rectangleCenter.EnableOutline(true);
    
    m_rectangleUp = sf::Shape::Rectangle(-5.0f, -55.0f, 10.0f, 10.0f, sf::Color::Blue);
    m_rectangleRight = sf::Shape::Rectangle(45.0f, -5.0f, 10.0f, 10.0f, sf::Color::Red);
    
    m_circleKnob = sf::Shape::Circle(50.0f, 0.0f, 5.0f, sf::Color::Red);
}

Gizmo::~Gizmo()
{
    
}

void Gizmo::update(float dt)
{
    if (g_Input.isMouseButtonFirstDown(sf::Mouse::Left))
    {
        sf::Vector2f worldPos = g_Window->ConvertCoords(g_Input.getMouseX(), g_Input.getMouseY());
        
        std::vector<Entity*> entities = m_currentScene->getEntitiesAtPosition(worldPos);
        
        Object* bestObject = NULL;
        for (int i = 0; i < (int)entities.size(); i++)
        {
            if (entities[i]->getType() == Entity::OBJECT)
            {
                if (bestObject == NULL || entities[i]->getDrawLayer() > bestObject->getDrawLayer())
                    bestObject = static_cast<Object*>(entities[i]);
            }
        }
        
        if (bestObject != NULL)
            m_selectedObject = bestObject;
    }
    
    if (g_Input.isMouseButtonDown(sf::Mouse::Left) && m_selectedObject != NULL && g_Input.getMouseDelta() != sf::Vector2i(0, 0))
    {
        sf::Vector2f objPos = m_selectedObject->getPosition();
        sf::Vector2f mousePos = g_Window->ConvertCoords(g_Input.getMouseX(), g_Input.getMouseY());
        
        switch (m_mode)
        {
            case Gizmo::MOVE:
            {
                if (!m_movingFree && !m_movingHorizontally && !m_movingVertically)
                {
                    sf::FloatRect upArrowRect(objPos.x - 10.0f, objPos.y - 50.0f - 10.0f, 20.0f, 20.0f);
                    sf::FloatRect rightArrowRect(objPos.x + 50.0f - 10.0f, objPos.y - 10.0f, 20.0f, 20.0f);
                    sf::FloatRect freeRect(objPos.x, objPos.y - 15.0f, 15.0f, 15.0f);
                    
                    if (freeRect.Contains(mousePos))
                    {
                        m_movingFree = true;
                    }
                    else if (upArrowRect.Contains(mousePos))
                    {
                        m_movingVertically = true;
                    }
                    else if (rightArrowRect.Contains(mousePos))
                    {
                        m_movingHorizontally = true;
                    }
                }
            }
            break;
            case Gizmo::ROTATE:
            {
                float angle = m_selectedObject->getRotation();
                sf::Vector2f dirNormal(cos(math::radians(angle)), sin(math::radians(angle)));
                sf::Vector2f knobPos = objPos + dirNormal * 50.0f;
                
                if (!m_rotating)
                {
                    sf::FloatRect knobRect(knobPos.x - 10.0f, knobPos.y - 10.0f, 20.0f, 20.0f);
                    
                    if (knobRect.Contains(mousePos))
                    {
                        m_rotating = true;
                    }
                }
            }
            break;
            case Gizmo::SCALE:
            {
                
            }
            break;
        }
    }
    else if (g_Input.isMouseButtonFirstUp(sf::Mouse::Left))
    {
        m_movingFree = false;
        m_movingHorizontally = false;
        m_movingVertically = false;
        m_rotating = false;
    }
    
    if (m_selectedObject != NULL)
    {
        sf::Vector2f objPos = m_selectedObject->getPosition();
        
        if (m_movingFree)
        {
            m_selectedObject->setPosition(sf::Vector2f(objPos.x + g_Input.getMouseDelta().x, objPos.y + g_Input.getMouseDelta().y));
        }
        else if (m_movingHorizontally)
        {
            m_selectedObject->setPosition(sf::Vector2f(objPos.x + g_Input.getMouseDelta().x, objPos.y));
        }
        else if (m_movingVertically)
        {
            m_selectedObject->setPosition(sf::Vector2f(objPos.x, objPos.y + g_Input.getMouseDelta().y));
        }
        else if (m_rotating)
        {
            sf::Vector2f mousePos = g_Window->ConvertCoords(g_Input.getMouseX(), g_Input.getMouseY());
            
            float objectMouseAngle = atan2(mousePos.y - objPos.y, mousePos.x - objPos.x);
            
            m_selectedObject->setRotation(math::degrees(objectMouseAngle));
        }
    }
    
    if (g_Input.isKeyFirstDown(sf::Key::T))
        m_mode = Gizmo::MOVE;
    else if (g_Input.isKeyFirstDown(sf::Key::R))
        m_mode = Gizmo::ROTATE;
    else if (g_Input.isKeyFirstDown(sf::Key::S))
        m_mode = Gizmo::SCALE;
}

void Gizmo::draw(sf::RenderTarget& target)
{
    if (m_selectedObject != NULL)
    {
        sf::Vector2f objPos = m_selectedObject->getPosition();
        
        switch (m_mode)
        {
            case Gizmo::MOVE:
            {
                m_lineUp.SetPosition(objPos);
                m_lineRight.SetPosition(objPos);
                m_triangleUp.SetPosition(objPos);
                m_triangleRight.SetPosition(objPos);
                m_rectangleCenter.SetPosition(objPos);
                
                target.Draw(m_rectangleCenter);
                target.Draw(m_lineUp);
                target.Draw(m_lineRight);
                target.Draw(m_triangleUp);
                target.Draw(m_triangleRight);
            }
            break;
            case Gizmo::ROTATE:
            {
                float angle = m_selectedObject->getRotation();
                sf::Vector2f dirNormal(cos(math::radians(angle)), sin(math::radians(angle)));
                
                m_lineRotate.SetPosition(objPos);
                m_lineRotate.SetRotation(angle);
                m_circleKnob.SetPosition(objPos);
                m_circleKnob.SetRotation(angle);
                
                target.Draw(m_lineRotate);
                target.Draw(m_circleKnob);
            }
            break;
            case Gizmo::SCALE:
            {
                float angle = m_selectedObject->getRotation();
                sf::Vector2f dirNormal(cos(math::radians(angle)), sin(math::radians(angle)));
                
                m_lineScaleBlue.SetPosition(objPos);
                m_lineScaleBlue.SetRotation(angle);
                m_lineScaleRed.SetPosition(objPos);
                m_lineScaleRed.SetRotation(angle);
                
                m_rectangleUp.SetRotation(angle);
                m_rectangleUp.SetPosition(objPos);
                m_rectangleRight.SetRotation(angle);
                m_rectangleRight.SetPosition(objPos);
                
                target.Draw(m_lineScaleBlue);
                target.Draw(m_lineScaleRed);
                target.Draw(m_rectangleUp);
                target.Draw(m_rectangleRight);
            }
            break;
        }
    }
}

void Gizmo::setMode(GizmoMode mode)
{
    m_mode = mode;
}

void Gizmo::setSelectedObject(Object* object)
{
    m_selectedObject = object;
}

Object* Gizmo::getSelectedObject() const
{
    return m_selectedObject;
}
