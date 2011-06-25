#include "Scene.h"

#include "Entities/Entity.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "../Game.h"
#include "../Scripting/Script.h"
#include "../Scripting/ScriptManager.h"

Scene::Scene(bool scriptingEnabled) :
    m_initialized(false),
    m_scriptingEnabled(scriptingEnabled),
    m_lightingEnabled(true),
    m_script(NULL),
    m_ambientColor(sf::Color::White),
    m_lightRenderer(1280, 720, 640, 360),
    m_b2World(b2Vec2(0.0f, 0.0f), true),
    m_meterPixelRatio(30.0f),
    m_debugDrawer(g_Window, m_meterPixelRatio, 1.0f, 0.3f)
{
    m_debugDrawer.SetFlags(DebugDrawer::e_shapeBit);
    m_b2World.SetDebugDraw(&m_debugDrawer);
    m_b2World.SetContactListener(&m_contactListener);
}

Scene::~Scene()
{
    std::cout << "Beginning Scene destruction" << std::endl;
    
    if (m_script != NULL)
        delete m_script;
    
    m_entities.clear();
    
    std::cout << "Destroying b2world" << std::endl;
    
    std::cout << m_b2World.GetBodyCount() << std::endl;
}

void Scene::load(const std::string& filename)
{
    std::ifstream in(filename.c_str());
    
    if (!in.is_open())
    {
        return;
    }
    
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(in, root))
    {
        std::cout << filename << ": " << reader.getFormatedErrorMessages() << std::endl;
        
        return;
    }
    
    in.close();
    
    m_name = root["name"].asString();
    
    m_scriptFile = root["script"].asString();
    
    if (m_scriptingEnabled)
    {
        m_script = new Script(&g_scriptManager, m_name);
        m_script->loadSection(m_scriptFile);
        m_script->build();
    }
    
    Json::Value objectsToLoad = root["load"];
    for (int i = 0; i < (int)objectsToLoad.size(); i++)
    {
        std::string filename = objectsToLoad[i].asString();
        
        m_objectDefFilenames.push_back(filename);
        
        ObjectDef def;
        def.load(filename);
        
        m_objectDefs.insert(std::pair<std::string, ObjectDef>(def.m_type, def));
    }
    
    Json::Value objects = root["objects"];
    for (int i = 0; i < (int)objects.size(); i++)
    {
        Json::Value object = objects[i];
        
        std::map<std::string, ObjectDef>::iterator it = m_objectDefs.find(object["type"].asString());
        
        if (it != m_objectDefs.end())
        {
            std::string id = object["id"].asString();
            int drawLayer = object["drawLayer"].asInt();
            parsing::Vector2 position = parsing::vector2(object["position"].asString());
            sf::Vector2f pos(position.x, position.y);
            float rotation = object["rotation"].asDouble();
            parsing::Vector2 sca = parsing::vector2(object["scale"].asString());
            sf::Vector2f scale(sca.x, sca.y);
            bool physics = object["physics"].asBool();
            
            Object* obj = new Object(this, id, &it->second, drawLayer, pos, rotation, scale, physics);
            
            addEntity(obj);
        }
    }
    
    parsing::Color4 ambientColor = parsing::color(root["ambientColor"].asString());
    m_ambientColor = sf::Color(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
    
    Json::Value lights = root["lights"];
    for (int i = 0; i < (int)lights.size(); i++)
    {
        Json::Value light = lights[i];
        
        std::string type = light["type"].asString();
        std::string id = light["id"].asString();
        parsing::Vector2 position = parsing::vector2(light["position"].asString());
        float radius = light["radius"].asDouble();
        float intensity = light["intensity"].asDouble();
        parsing::Color4 color = parsing::color(light["color"].asString());
        
        if (type.compare("point") == 0)
        {
            int quality = light["quality"].asInt();
            
            Light* lightPtr = new PointLight(id, sf::Vector2f(position.x, position.y), intensity, radius, sf::Color(color.r, color.g, color.b, color.a), quality);
            
            m_lights.insert(id, lightPtr);
        }
        else if (type.compare("spot") == 0)
        {
           float angle = light["angle"].asDouble();
           float openAngle = light["openAngle"].asDouble();
           
           Light* lightPtr = new SpotLight(id, sf::Vector2f(position.x, position.y), intensity, radius, sf::Color(color.r, color.g, color.b, color.a), angle, openAngle);
           
           m_lights.insert(id, lightPtr);
        }
    }
}

void Scene::save(const std::string& filename)
{
    Json::Value root;
    
    root["name"] = m_name;
    root["script"] = m_scriptFile;
    
    Json::Value load(Json::arrayValue);
    for (int i = 0; i < (int)m_objectDefFilenames.size(); i++)
    {
        load.append(m_objectDefFilenames[i]);
    }
    root["load"] = load;
    
    Json::Value objects(Json::arrayValue);
    for (int i = 0; i < (int)m_entities.size(); i++)
    {
        if (m_entities[i].getType() == Entity::OBJECT)
        {
            Object* obj = static_cast<Object*>(&m_entities[i]);
            
            Json::Value object;
            
            object["type"] = obj->getObjectDef()->m_type;
            object["id"] = obj->getId();
            object["drawLayer"] = obj->getDrawLayer();
            object["physics"] = obj->hasPhysics();
            object["position"] = boost::str(boost::format("%1% %2%") % obj->getPosition().x % obj->getPosition().y);
            object["rotation"] = obj->getRotation();
            object["scale"] = boost::str(boost::format("%1% %2%") % obj->getScale().x % obj->getScale().y);
            
            objects.append(object);
        }
    }
    root["objects"] = objects;
    
    root["ambientColor"] = boost::str(boost::format("%1% %2% %3%") % m_ambientColor.r % m_ambientColor.g % m_ambientColor.b);
    
    Json::Value lights(Json::arrayValue);
    boost::ptr_map<std::string, Light>::iterator it;
    for (it = m_lights.begin(); it != m_lights.end(); it++)
    {
        Json::Value light;
        
        Light* lightPtr = it->second;
        
        light["type"] = lightPtr->getType() == Light::LT_POINT ? "point" : "spot";
        light["id"] = lightPtr->getId();
        light["position"] = boost::str(boost::format("%1% %2%") % lightPtr->getPosition().x % lightPtr->getPosition().y);
        light["radius"] = lightPtr->getRadius();
        light["intensity"] = lightPtr->getIntensity();
        light["color"] = boost::str(boost::format("%1% %2% %3%") % m_ambientColor.r % m_ambientColor.g % m_ambientColor.b);
        
        if (lightPtr->getType() == Light::LT_POINT)
        {
            PointLight* pointLight = static_cast<PointLight*>(lightPtr);
            
            light["quality"] = pointLight->getQuality();
        }
        else if (lightPtr->getType() == Light::LT_SPOT)
        {
            SpotLight* spotLight = static_cast<SpotLight*>(lightPtr);
            
            light["angle"] = spotLight->getAngle();
            light["openAngle"] = spotLight->getOpenAngle();
        }
        
        lights.append(light);
    }
    root["lights"] = lights;
    
    std::ofstream out(filename.c_str());
    
    if (!out.is_open())
    {
        return;
    }
    
    Json::StyledStreamWriter writer;
    writer.write(out, root);
    
    out.close();
}

void Scene::update(float dt)
{
    // Run the script update function
    if (m_script != NULL && m_scriptingEnabled)
    {
        if (!m_initialized)
        {
            m_script->prepareFunction("initialize");
            m_script->executeFunction();
            
            m_initialized = true;
        }
        
        m_script->prepareFunction("update");
        m_script->setArgFloat(0, dt);
        m_script->executeFunction();
    }
    
    // Update all the entities
    for (int i = 0; i < (int)m_entities.size(); i++)
    {
        m_entities[i].update(dt);
    }
    
    // Sort the entities based on drawing layer.
    m_entities.sort(m_entities.begin(), m_entities.end());
    
    for (int i = 0; i < (int)m_particleSystems.size(); i++)
    {
        m_particleSystems[i].update(dt);
    }
    
    // Update the Box2D world
    m_b2World.Step(1.0f / 60.0f, 6, 2);
    m_b2World.ClearForces();
    
    // Go through the list of entities to remove and remove them
    for (int i = 0; i < (int)m_entitiesToRemove.size(); i++)
    {
        for (int j = 0; j < (int)m_entities.size(); j++)
        {
            if (m_entities[j].getId() == m_entitiesToRemove[i])
            {
                m_entities.erase(m_entities.begin() + j);
                
                break;
            }
        }
    }
    m_entitiesToRemove.clear(); 
}

void Scene::draw(sf::RenderTarget& target)
{
    for (int i = 0; i < (int)m_entities.size(); i++)
    {
         m_entities[i].draw(target);
    }
    
    for (int i = 0; i < (int)m_particleSystems.size(); i++)
    {
        m_particleSystems[i].draw(target);
    }
    
    if (m_lightingEnabled)
    {
        m_lightRenderer.setLights(&m_lights);
        m_lightRenderer.setAmbientColor(m_ambientColor);
        m_lightRenderer.draw(target);
    }
    
    //m_b2World.DrawDebugData();
}

bool Scene::isScriptingEnabled() const
{
    return m_scriptingEnabled;
}

void Scene::setScriptingEnabled(bool enabled)
{
    m_scriptingEnabled = enabled;
}

void Scene::addEntity(Entity* entity)
{
    entity->setScene(this);
    
    m_entities.push_back(entity);
}

Entity* Scene::getEntityById(const std::string& id)
{
    for (int i = 0; i < (int)m_entities.size(); i++)
    {
        if (m_entities[i].getId() == id)
        {
            return &m_entities[i];
        }
    }
    
    return NULL;
}

std::vector<Entity*> Scene::getEntitiesAtPosition(const sf::Vector2f& pos)
{
    std::vector<Entity*> entities;
    
    b2Vec2 physicsPosition(pos.x / m_meterPixelRatio, pos.y / m_meterPixelRatio);
    
    for (int i = 0; i < (int)m_entities.size(); i++)
    {
        if (m_entities[i].hasPhysics())
        {
            b2Body* body = m_entities[i].getBody();
            
            if (body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), physicsPosition))
            {
                entities.push_back(&m_entities[i]);
            }
        }
    }
    
    return entities;
}

void Scene::scheduleEntityForRemoval(Entity* entity)
{
    m_entitiesToRemove.push_back(entity->getId());
}

bool Scene::isLightingEnabled() const
{
    return m_lightingEnabled;
}

void Scene::setLightingEnabled(bool enabled)
{
    m_lightingEnabled = enabled;
}

void Scene::setAmbientColor(const sf::Color& ambientColor)
{
    m_ambientColor = ambientColor;
}

void Scene::addLight(Light* light)
{
    std::string key = light->getId();
    m_lights.insert(key, light);
}

Light* Scene::getLightById(const std::string& id)
{
    boost::ptr_map<std::string, Light>::iterator it;
    for (it = m_lights.begin(); it != m_lights.end(); it++)
    {
        if (it->second->getId() == id)
        {
            return it->second;
        }
    }
    
    return NULL;
}

void Scene::loadParticleSystem(const std::string& filename)
{
    ParticleSystem ps;
    ps.load(filename);
    
    m_particleSystems.push_back(ps);
    
    std::sort(m_particleSystems.begin(), m_particleSystems.end());
}

void Scene::fireParticleSystem(const std::string& name, const sf::Vector2f& pos)
{
    for (int i = 0; i < (int)m_particleSystems.size(); i++)
    {
        if (m_particleSystems[i].getName() == name)
        {
            m_particleSystems[i].fire(pos);
            
            break;
        }
    }
}

b2World* Scene::getB2World()
{
    return &m_b2World;
}

float Scene::getMeterPixelRatio()
{
    return m_meterPixelRatio;
}

std::string Scene::getRandomId(const std::string& prefix)
{
    int randomId = math::rand(0, 10000000);
    
    return boost::str(boost::format("%1%%2%") % prefix % randomId);
}
