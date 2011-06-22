#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "ContactListener.h"
#include "DebugDrawer.h"
#include "Entities/Object.h"
#include "ParticleSystem.h"
#include "../Parsing.h"
#include "../Renderers/LightRenderer.h"

class Entity;
class Light;
class Script;

class Scene
{
public:
    Scene(bool scriptingEnabled);
    ~Scene();
    
    void load(const std::string& filename);
    void save(const std::string& filename); 
    
    void update(float dt);
    void draw(sf::RenderTarget& target);
    
    bool isScriptingEnabled() const;
    void setScriptingEnabled(bool enabled);
    
    void addEntity(Entity* entity);
    Entity* getEntityById(const std::string& id);
    std::vector<Entity*> getEntitiesAtPosition(const sf::Vector2f& pos);
    void scheduleEntityForRemoval(Entity* entity);
    
    bool isLightingEnabled() const;
    void setLightingEnabled(bool enabled);
    
    void setAmbientColor(const sf::Color& ambientColor);
    
    void addLight(Light* light);
    Light* getLightById(const std::string& id);
    
    void loadParticleSystem(const std::string& filename);
    void fireParticleSystem(const std::string& name, const sf::Vector2f& pos);
    
    b2World* getB2World();
    
    float getMeterPixelRatio();
    
    std::string getRandomId(const std::string& prefix);

private:
    std::string m_name;
    
    bool m_initialized;
    
    bool m_scriptingEnabled;
    std::string m_scriptFile;
    Script* m_script;
    
    std::map<std::string, ObjectDef> m_objectDefs;
    
    std::vector<std::string> m_entitiesToRemove;
    boost::ptr_vector<Entity> m_entities;
    
    bool m_lightingEnabled;
    sf::Color m_ambientColor;
    boost::ptr_map<std::string, Light> m_lights;
    LightRenderer m_lightRenderer;
    
    std::vector<ParticleSystem> m_particleSystems;
    
    b2World m_b2World;
    float m_meterPixelRatio;
    
    ContactListener m_contactListener;
    DebugDrawer m_debugDrawer;
};

#endif // SCENE_H_INCLUDED
