#include "Scene.h"

Scene::Scene() :
    m_script(NULL),
    m_ambientColor(sf::Color::White),
    m_lightRenderer(1280, 720, 640, 360),
    m_b2World(b2Vec2(0.0f, 0.0f), true),
    m_meterPixelRatio(30.0f),
    m_debugDrawer(g_Window, m_meterPixelRatio, 1.0f, 0.3f)
{
    m_debugDrawer.SetFlags(DebugDrawer::e_shapeBit);
    m_b2World.SetDebugDraw(&m_debugDrawer);
}

Scene::~Scene()
{
    if (m_script != NULL)
        delete m_script;
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
    m_script = new Script(&g_ScriptManager, m_name);
    m_script->loadSection(m_scriptFile);
    m_script->build();
    
    Json::Value objectsToLoad = root["load"];
    for (int i = 0; i < objectsToLoad.size(); i++)
    {
        ObjectDef def;
        def.load(objectsToLoad[i].asString());
        
        m_objectDefs.insert(std::pair<std::string, ObjectDef>(def.m_type, def));
    }
    
    Json::Value objects = root["objects"];
    for (int i = 0; i < objects.size(); i++)
    {
        Json::Value object = objects[i];
        
        std::map<std::string, ObjectDef>::iterator it = m_objectDefs.find(object["type"].asString());
        
        if (it != m_objectDefs.end())
        {
            Object obj(this, &it->second, object["physics"].asBool());
            
            obj.setId(object["id"].asString());
            parsing::Vector2 position = parsing::vector2(object["position"].asString());
            obj.setPosition(position.x, position.y);
            obj.setRotation(object["rotation"].asDouble());
            obj.setScale(object["scale"].asDouble());
            
            m_objects.push_back(obj);
        }
    }
    
    parsing::Color4 ambientColor = parsing::color(root["ambientColor"].asString());
    m_ambientColor = sf::Color(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
    
    Json::Value lights = root["lights"];
    for (int i = 0; i < lights.size(); i++)
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
            
            LightPtr lightPtr(new PointLight(id, sf::Vector2f(position.x, position.y), intensity, radius, sf::Color(color.r, color.g, color.b, color.a), quality));
            
            m_lights.insert(std::pair<std::string, LightPtr>(id, lightPtr));
        }
        else if (type.compare("spot") == 0)
        {
           float angle = light["angle"].asDouble();
           float openAngle = light["openAngle"].asDouble();
           
           LightPtr lightPtr(new SpotLight(id, sf::Vector2f(position.x, position.y), intensity, radius, sf::Color(color.r, color.g, color.b, color.a), angle, openAngle));
           
           m_lights.insert(std::pair<std::string, LightPtr>(id, lightPtr));
        }
    }
}

void Scene::save(const std::string& filename)
{
    
}

void Scene::update(float dt)
{
    if (m_script != NULL)
    {
        m_script->prepareFunction("update");
        m_script->setArgFloat(0, dt);
        m_script->executeFunction();
    }
    
    
}

void Scene::draw(sf::RenderTarget& target)
{
    for (int i = 0; i < m_objects.size(); i++)
    {
         m_objects[i].draw(target);
    }
    
    m_lightRenderer.setLights(m_lights);
    m_lightRenderer.setAmbientColor(m_ambientColor);
    m_lightRenderer.draw(target);
    
    m_b2World.DrawDebugData();
}

void Scene::addLight(LightPtr light)
{
    m_lights.insert(std::pair<std::string, LightPtr>(light->getName(), light));
}

LightPtr Scene::getLightByName(const std::string& name)
{
    std::map<std::string, LightPtr>::iterator it = m_lights.find(name);
    
    if (it != m_lights.end())
    {
        return it->second;
    }
    
    return LightPtr();
}

b2World* Scene::getB2World()
{
    return &m_b2World;
}

float Scene::getMeterPixelRatio()
{
    return m_meterPixelRatio;
}
