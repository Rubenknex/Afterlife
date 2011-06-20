#include "Object.h"

#include "Scene.h"

void ObjectDef::load(const std::string& filename)
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
        return;
    }
    
    m_type = root["type"].asString();
    m_imageFile = root["image"].asString();
    
    Json::Value vertices = root["vertices"];
    for (int i = 0; i < vertices.size(); i++)
    {
        std::vector<std::string> parts;
        std::string vertexString = vertices[i].asString();
        boost::algorithm::split(parts, vertexString, boost::algorithm::is_any_of(" "));
        
        b2Vec2 vertex;
        vertex.x = atof(parts[0].c_str());
        vertex.y = atof(parts[1].c_str());
        
        m_vertices.push_back(vertex);
    }
    
    m_friction = root["friction"].asDouble();
    m_density = root["density"].asDouble();
    m_restitution = root["restitution"].asDouble();
}

void ObjectDef::save(const std::string& filename)
{
    Json::Value root;
    
    root["type"] = m_type;
    root["image"] = m_imageFile;
    
    Json::Value vertices(Json::arrayValue);
    for (int i = 0; i < m_vertices.size(); i++)
    {
        std::string vertex = boost::str(boost::format("%1% %2%") % m_vertices[i].x % m_vertices[i].y);
        
        vertices.append(Json::Value(vertex));
    }
    root["vertices"] = vertices;
    
    root["friction"] = m_friction;
    root["density"] = m_density;
    root["restitution"] = m_restitution;
    
    std::ofstream out(filename.c_str());
    
    if (!out.is_open())
    {
        return;
    }
    
    Json::StyledStreamWriter writer;
    writer.write(out, root);
    
    out.close();
}

Object::Object(Scene* scene, ObjectDef* def, bool physics) :
    m_scene(scene),
    m_def(def),
    m_physics(physics)
{
    m_image = IM.GetResource(m_def->m_imageFile);
    m_image->SetSmooth(true);
    m_sprite.SetImage(*m_image);
    
    // Set the origin to the center for proper rotation.
    m_sprite.SetOrigin(m_sprite.GetSize() / 2.0f);
    
    if (m_physics)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(0.0f, 0.0f);
        
        m_body = m_scene->getB2World()->CreateBody(&bodyDef);
        
        b2PolygonShape shape;
        
        // Transform the vertices to meters instead of pixels.
        std::vector<b2Vec2> transformedVertices;
        for (int i = 0; i < m_def->m_vertices.size(); i++)
        {
            transformedVertices.push_back(b2Vec2(m_def->m_vertices[i].x / m_scene->getMeterPixelRatio(), m_def->m_vertices[i].y / m_scene->getMeterPixelRatio()));
        }
        
        shape.Set(&transformedVertices[0], transformedVertices.size());
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = m_def->m_friction;
        fixtureDef.density = m_def->m_density;
        fixtureDef.restitution = m_def->m_restitution;
        
        m_body->CreateFixture(&fixtureDef);
    }
}

Object::~Object()
{
    
}

void Object::draw(sf::RenderTarget& target)
{
    target.Draw(m_sprite);
}

void Object::setId(const std::string& id)
{
    m_id = id;
}

void Object::setPosition(float x, float y)
{
    m_sprite.SetPosition(x, y);
    
    if (m_physics)
        m_body->SetTransform(b2Vec2(x / m_scene->getMeterPixelRatio(), y / m_scene->getMeterPixelRatio()), math::radians(m_sprite.GetRotation()));
}

void Object::setRotation(float degrees)
{
    m_sprite.SetRotation(degrees);
    
    if (m_physics)
    {
        b2Transform transform = m_body->GetTransform();
        m_body->SetTransform(transform.position, math::radians(degrees));
    }
}

void Object::setScale(float scale)
{
    m_sprite.SetScale(scale, scale);
    
    if (m_physics)
    {
        b2PolygonShape shape;
        
        // Transform the vertices to meters instead of pixels.
        std::vector<b2Vec2> transformedVertices;
        for (int i = 0; i < m_def->m_vertices.size(); i++)
        {
            transformedVertices.push_back(b2Vec2((m_def->m_vertices[i].x / m_scene->getMeterPixelRatio()) * scale, (m_def->m_vertices[i].y / m_scene->getMeterPixelRatio()) * scale));
        }
        
        shape.Set(&transformedVertices[0], transformedVertices.size());
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = m_def->m_friction;
        fixtureDef.density = m_def->m_density;
        fixtureDef.restitution = m_def->m_restitution;
        
        m_body->DestroyFixture(m_body->GetFixtureList());
        m_body->CreateFixture(&fixtureDef);
    }
}
