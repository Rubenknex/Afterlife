#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <json/json.h>
#include <map>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Light.h"
#include "Object.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "../DebugDrawer.h"
#include "../Game.h"
#include "../Parsing.h"
#include "../Renderers/LightRenderer.h"
#include "../Scripting/Script.h"
#include "../Scripting/ScriptManager.h"

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
    
    void addLight(LightPtr light);
    LightPtr getLightByName(const std::string& name);
    
    b2World* getB2World();
    
    float getMeterPixelRatio();

private:
    std::string m_name;
    
    std::string m_scriptFile;
    Script* m_script;
    
    std::map<std::string, ObjectDef> m_objectDefs;
    std::vector<Object> m_objects;
    
    sf::Color m_ambientColor;
    std::map<std::string, LightPtr> m_lights;
    
    LightRenderer m_lightRenderer;
    
    b2World m_b2World;
    float m_meterPixelRatio;
    DebugDrawer m_debugDrawer;
};

#endif // SCENE_H_INCLUDED
