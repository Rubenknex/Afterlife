#include "ParticleSystem.h"
 
ParticleSystem::ParticleSystem()
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        m_particles[i].pos = sf::Vector2f();
        m_particles[i].vel = sf::Vector2f();
        m_particles[i].scale = 1.0f;
        m_particles[i].rotation = 0.0f;
        m_particles[i].timeAlive = 0.0f;
        m_particles[i].lifeSpan = 0.0f;
        m_particles[i].alive = false;
    }
}

ParticleSystem::~ParticleSystem()
{
    
}
 
void ParticleSystem::load(const std::string& filename)
{
    /*
    TiXmlDocument doc;
 
    if (doc.LoadFile(filename))
    {
        TiXmlHandle handle(&doc);
        handle = handle.FirstChild("ParticleSystem");
 
        TiXmlElement* texture = handle.FirstChild("Texture").ToElement();
        m_texture.SetImage(*IM.GetResource(texture->FirstChild()->ValueStr()));
        m_texture.SetOrigin(m_texture.GetSize() / 2.0f);
 
        TiXmlElement* color = handle.FirstChild("Color").ToElement();
        int r = boost::lexical_cast<int>(color->Attribute("R"));
        int g = boost::lexical_cast<int>(color->Attribute("G"));
        int b = boost::lexical_cast<int>(color->Attribute("B"));
        mColor = sf::Color(r, g, b);
 
        TiXmlElement* drawOrder = handle.FirstChild("DrawOrder").ToElement();
        mDrawOrder = boost::lexical_cast<int>(drawOrder->FirstChild()->ValueStr());
 
        TiXmlElement* minSpeed = handle.FirstChild("MinSpeed").ToElement();
        mMinSpeed = boost::lexical_cast<float>(minSpeed->FirstChild()->ValueStr());
        TiXmlElement* maxSpeed = handle.FirstChild("MaxSpeed").ToElement();
        mMaxSpeed = boost::lexical_cast<float>(maxSpeed->FirstChild()->ValueStr());
 
        TiXmlElement* minAngle = handle.FirstChild("MinAngle").ToElement();
        mMinAngle = boost::lexical_cast<float>(minAngle->FirstChild()->ValueStr());
        TiXmlElement* maxAngle = handle.FirstChild("MaxAngle").ToElement();
        mMaxAngle = boost::lexical_cast<float>(maxAngle->FirstChild()->ValueStr());
 
        TiXmlElement* minScale = handle.FirstChild("MinScale").ToElement();
        mMinScale = boost::lexical_cast<float>(minScale->FirstChild()->ValueStr());
        TiXmlElement* maxScale = handle.FirstChild("MaxScale").ToElement();
        mMaxScale = boost::lexical_cast<float>(maxScale->FirstChild()->ValueStr());
 
        TiXmlElement* minRotation = handle.FirstChild("MinRotation").ToElement();
        mMinRotation = boost::lexical_cast<float>(minRotation->FirstChild()->ValueStr());
        TiXmlElement* maxRotation = handle.FirstChild("MaxRotation").ToElement();
        mMaxRotation = boost::lexical_cast<float>(maxRotation->FirstChild()->ValueStr());
 
        TiXmlElement* minLifespan = handle.FirstChild("MinLifespan").ToElement();
        mMinLifespan = boost::lexical_cast<float>(minLifespan->FirstChild()->ValueStr());
        TiXmlElement* maxLifespan = handle.FirstChild("MaxLifespan").ToElement();
        mMaxLifespan = boost::lexical_cast<float>(maxLifespan->FirstChild()->ValueStr());
 
        TiXmlElement* minParticles = handle.FirstChild("MinParticles").ToElement();
        mMinParticles = boost::lexical_cast<int>(minParticles->FirstChild()->ValueStr());
        TiXmlElement* maxParticles = handle.FirstChild("MaxParticles").ToElement();
        mMaxParticles = boost::lexical_cast<int>(maxParticles->FirstChild()->ValueStr());
    }
    else
    {
        std::cout << "Failed to load ParticleSystem: " << filename << std::endl;
    }
    */
    
    std::ifstream in(filename.c_str());
    
    if (!in.is_open())
    {
        std::cout << "Failed to open " << filename << std::endl;
        
        return;
    }
    
    Json::Value root;
    Json::Reader reader;
    
    if (!reader.parse(in, root))
    {
        std::cout << "Failed to parse " << filename << ": " << reader.getFormatedErrorMessages() << std::endl;
        
        return;
    }
    
    m_name = root["name"].asString();
    
    m_texture.SetImage(*IM.GetResource(root["texture"].asString()));
    
    parsing::Color4 color = parsing::color(root["color"].asString());
    m_color = sf::Color(color.r, color.g, color.b, color.a);
    
    m_drawOrder = root["drawOrder"].asInt();
    
    m_minSpeed = root["minSpeed"].asDouble();
    m_maxSpeed = root["maxSpeed"].asDouble();
    
    m_minAngle = root["minAngle"].asDouble();
    m_maxAngle = root["maxAngle"].asDouble();
    
    m_minScale = root["minScale"].asDouble();
    m_maxScale = root["maxScale"].asDouble();
    
    m_minRotation = root["minRotation"].asDouble();
    m_maxRotation = root["maxRotation"].asDouble();
    
    m_minLifeSpan = root["minLifeSpan"].asDouble();
    m_maxLifeSpan = root["maxLifeSpan"].asDouble();
    
    m_minParticles = root["minParticles"].asInt();
    m_maxParticles = root["maxParticles"].asInt();
}
 
void ParticleSystem::fire(sf::Vector2f pos)
{
    int num_particles = sf::Randomizer::Random(m_minParticles, m_maxParticles);
    int particleCounter = 0;
    
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!m_particles[i].alive)
        {
            m_particles[i].pos = pos;
            float angle = sf::Randomizer::Random(m_minAngle, m_maxAngle);
            float speed = sf::Randomizer::Random(m_minSpeed, m_maxSpeed);
            m_particles[i].vel = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
            m_particles[i].rotation = sf::Randomizer::Random(m_minRotation, m_maxRotation);
            m_particles[i].scale = sf::Randomizer::Random(m_minScale, m_maxScale);
            m_particles[i].timeAlive = 0.0f;
            m_particles[i].lifeSpan = sf::Randomizer::Random(m_minLifeSpan, m_maxLifeSpan);
            m_particles[i].alive = true;
 
            particleCounter++;
        }
        
        if (particleCounter >= num_particles)
            break;
    }
}
 
void ParticleSystem::update(float dt)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (m_particles[i].alive)
        {
            m_particles[i].pos += m_particles[i].vel * dt;
            m_particles[i].timeAlive += dt;
            
            if (m_particles[i].timeAlive > m_particles[i].lifeSpan)
            {
                m_particles[i].alive = false;
            }
        }
    }
}
 
void ParticleSystem::draw(sf::RenderTarget& target)
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (m_particles[i].alive)
        {
            m_texture.SetPosition(m_particles[i].pos);
            m_texture.SetScale(m_particles[i].scale, m_particles[i].scale);
            m_texture.SetRotation(m_particles[i].rotation);
            
            int alpha = 255 - ((m_particles[i].timeAlive / m_particles[i].lifeSpan) * 255);
            m_texture.SetColor(sf::Color(m_color.r, m_color.g, m_color.b, alpha));
            
            target.Draw(m_texture);
        }
    }
}

const std::string& ParticleSystem::getName() const
{
    return m_name;
}
 
bool ParticleSystem::operator<(const ParticleSystem& rhs) const
{
    return m_drawOrder < rhs.m_drawOrder;
}
 
