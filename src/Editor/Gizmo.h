#ifndef GIZMO_H_INCLUDED
#define GIZMO_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class Object;
class Scene;

class Gizmo
{
public:
    enum GizmoMode
    {
        GM_MOVE,
        GM_ROTATE,
        GM_SCALE,
    };

    enum EditMode
    {
        EM_NONE,
        EM_MOVE_FREE,
        EM_MOVE_GLOBAL_X,
        EM_MOVE_GLOBAL_Y,
        EM_ROTATE_FREE,
        EM_SCALE_LOCAL_X,
        EM_SCALE_LOCAL_Y,
    };
    
public:
    Gizmo(Scene* scene);
    ~Gizmo();
    
    void update(float dt);
    void draw(sf::RenderTarget& taret);
    
    void setMode(GizmoMode mode);
    
    void setSelectedObject(Object* object);
    Object* getSelectedObject() const;

private:
    Scene* m_currentScene;
    
    GizmoMode m_gizmoMode;
    EditMode m_editMode;

    Object* m_selectedObject;
    
    sf::Shape m_triangleUp;
    sf::Shape m_triangleRight;
    sf::Shape m_lineUp;
    sf::Shape m_lineRight;
    sf::Shape m_lineRotate;
    sf::Shape m_lineScaleBlue;
    sf::Shape m_lineScaleRed;
    sf::Shape m_rectangleCenter;
    sf::Shape m_rectangleUp;
    sf::Shape m_rectangleRight;
    sf::Shape m_circleKnob;
};

#endif // GIZMO_H_INCLUDED
