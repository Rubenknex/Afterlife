#include "Actor.h"

Actor::Actor(Scene* scene) :
    m_scene(scene),
    m_body(NULL),
    m_script(NULL)
{
    
}

Actor::~Actor()
{
    if (m_script != NULL)
        delete m_script;
}

std::string Actor::getId()
{
    return m_id;
}

std::string Actor::getType()
{
    return m_type;
}
