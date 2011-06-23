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

#include "Entity.h"
#include "../../Functions.h"
#include "../../Math.h"
#include "../../ResourceManager.h"

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

class Object : public Entity
{
public:
    Object(Scene* scene, const std::string& id, ObjectDef* def, int drawLayer, const sf::Vector2f& pos, float degrees, const sf::Vector2f& scale, bool usePhysics);
    ~Object();
    
    void draw(sf::RenderTarget& target);
    
    const sf::Vector2f& getScale() const;
    void setScale(const sf::Vector2f& scale);
    
    ObjectDef* getObjectDef() const;

private:
    ObjectDef* m_def;
    boost::shared_ptr<sf::Image> m_image;
};

#endif // OBJECT_H_INCLUDED

