#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <Box2D/Box2D.h>
#include <fstream>
#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Math.h"
#include "../ResourceManager.h"

class Scene;

class ObjectDef
{
public:
    void load(const std::string& filename);
    void save(const std::string& filename);

public:
    std::string m_type;
    std::string m_imageFile;
    std::vector<b2Vec2> m_vertices;
    float m_friction;
    float m_density;
    float m_restitution;
};

class Object
{
public:
    Object(Scene* scene, ObjectDef* def, bool physics);
    ~Object();
    
    void draw(sf::RenderTarget& target);

    void setId(const std::string& id);
    void setPosition(float x, float y);
    void setRotation(float degrees);
    void setScale(float scale);

private:
    Scene* m_scene;

    ObjectDef* m_def;
    std::string m_id;
    boost::shared_ptr<sf::Image> m_image;
    sf::Sprite m_sprite;
    bool m_physics;
    b2Body* m_body;
};

#endif // OBJECT_H_INCLUDED

