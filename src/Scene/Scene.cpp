#include "Scene.h"

Scene::Scene() :
    m_initialized(false),
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
    m_script = new Script(&g_scriptManager, m_name);
    m_script->loadSection(m_scriptFile);
    m_script->build();
    
    Json::Value objectsToLoad = root["load"];
    for (int i = 0; i < (int)objectsToLoad.size(); i++)
    {
        ObjectDef def;
        def.load(objectsToLoad[i].asString());
        
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
            float scale = object["scale"].asDouble();
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
    
}

void Scene::update(float dt)
{
    // Run the script update function
    if (m_script != NULL)
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
    
    m_lightRenderer.setLights(&m_lights);
    m_lightRenderer.setAmbientColor(m_ambientColor);
    m_lightRenderer.draw(target);
    
    //m_b2World.DrawDebugData();
}

void Scene::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
    
    //std::cout << "Sorting Entities" << std::endl;
    
    //m_entities.sort(m_entities.begin(), m_entities.end());
    
    //std::cout << "Draw Layers:" << std::endl;
    //for (int i = 0; i < m_entities.size(); i++)
    //{
    //    std::cout << m_entities[i].getId() << ": " << m_entities[i].getDrawLayer() << std::endl;
    //}
}

Entity* Scene::getEntityById(const std::string& id)
{
    for (int i = 0; i < m_entities.size(); i++)
    {
        if (m_entities[i].getId() == id)
        {
            return &m_entities[i];
        }
    }
    
    return NULL;
}

void Scene::scheduleEntityForRemoval(Entity* entity)
{
    m_entitiesToRemove.push_back(entity->getId());
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
