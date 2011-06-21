#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <boost/ptr_container/ptr_vector.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <json/json.h>
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>

#include "ContactListener.h"
#include "DebugDrawer.h"
#include "Entities/Entity.h"
#include "Entities/Object.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "../Game.h"
#include "../Parsing.h"
#include "../Renderers/LightRenderer.h"
#include "../Scripting/Script.h"
#include "../Scripting/ScriptManager.h"

typedef boost::shared_ptr<Entity> EntityPtr;
typedef boost::shared_ptr<Light> LightPtr;

class Scene
{
public:
    Scene();
    ~Scene();
    
    void load(const std::string& filename);
    void save(const std::string& filename); 
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    void addEntity(Entity* entity);
    void scheduleEntityForRemoval(Entity* entity);
    
    void addLight(LightPtr light);
    LightPtr getLightByName(const std::string& name);
    
    b2World* getB2World();
    
    float getMeterPixelRatio();

private:
    std::string m_name;
    
    std::string m_scriptFile;
    Script* m_script;
    
    std::map<std::string, ObjectDef> m_objectDefs;
    
    std::vector<std::string> m_entitiesToRemove;
    boost::ptr_vector<Entity> m_entities;
    
    sf::Color m_ambientColor;
    std::map<std::string, LightPtr> m_lights;
    
    LightRenderer m_lightRenderer;
    
    b2World m_b2World;
    float m_meterPixelRatio;
    
    ContactListener m_contactListener;
    DebugDrawer m_debugDrawer;
};

#endif // SCENE_H_INCLUDED
