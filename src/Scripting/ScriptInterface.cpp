#include "ScriptInterface.h"

#include <cmath>
#include <SFML/Audio.hpp>

#include "../AudioPlayer.h"
#include "../InputState.h"
#include "../ResourceManager.h"
#include "../Scene/PointLight.h"
#include "../Scene/Scene.h"
#include "../Scene/SpotLight.h"
#include "../Scene/Entities/Entity.h"
#include "../Scene/Entities/Player.h"
#include "../Scene/Entities/Zombie.h"

Scene* g_scriptingScene = NULL;

void setScriptingScene(Scene* scene)
{
    g_scriptingScene = scene;
}

/// Vec2 ///
class Vec2
{
public:
    Vec2() : x(0.0f), y(0.0f) { }
    Vec2(const sf::Vector2f v) : x(v.x), y(v.y) { }
    Vec2(float x, float y) : x(x), y(y) { }

    Vec2& operator=(const Vec2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    Vec2 operator+(const Vec2& rhs)
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    Vec2 operator-(const Vec2& rhs)
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    Vec2 operator*(float rhs)
    {
        return Vec2(x * rhs, y * rhs);
    }

    Vec2 operator/(float rhs)
    {
        return Vec2(x / rhs, y / rhs);
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(float other)
    {
        x *= other;
        y *= other;
        return *this;
    }

    Vec2& operator/=(float other)
    {
        x /= other;
        y /= other;
        return *this;
    }

    float getLength()
    {
        return sqrt(x * x + y * y);
    }

    float getLengthSquared()
    {
        return x * x + y * y;
    }

    void normalize()
    {
        float length = getLength();
        x /= length;
        y /= length;
    }

    sf::Vector2f toVector2f()
    {
        return sf::Vector2f(x, y);
    }

public:
    float x;
    float y;
};

void asVec2Constructor(Vec2* self)
{
    new(self) Vec2();
}

void asVec2InitConstructor(Vec2* self, float x, float y)
{
    new(self) Vec2(x, y);
}

/// General ///
void asPrint(const std::string& msg)
{
    std::cout << msg << std::endl;
}

float asLerp(float value, float start, float end)
{
    return start + value * (start - end);
}

Vec2 asGetWindowSize()
{
    return Vec2((float)g_Window->GetWidth(), (float)g_Window->GetHeight());
}

/// Input ///
bool asIsKeyDown(const std::string& key)
{
    return g_Input.isKeyDown(g_Input.getKeyCode(key));
}

/// Random numbers ///
int asRandInt(int min, int max)
{
    return sf::Randomizer::Random(min, max);
}

float asRandFloat(float min, float max)
{
    return sf::Randomizer::Random(min, max);
}

/// Lights ///
void asAddSpotLight(const std::string& id, Vec2& pos, float intensity, float radius, int r, int g, int b, float angle, float openAngle)
{
    SpotLight* light = new SpotLight(id, pos.toVector2f(), intensity, radius, sf::Color(r, g, b), angle, openAngle);
    g_scriptingScene->addLight(light);
}

void asAddPointLight(const std::string& id, Vec2& pos, float intensity, float radius, int r, int g, int b, int quality)
{
    PointLight* light = new PointLight(id, pos.toVector2f(), intensity, radius, sf::Color(r, g, b), quality);
    g_scriptingScene->addLight(light);
}

Vec2 asGetLightPosition(const std::string& id)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        return Vec2(light->getPosition());

    std::cout << "Light: " << id << " not found." << std::endl;

    return Vec2();
}

void asSetLightPosition(const std::string& id, Vec2& pos)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        light->setPosition(pos.toVector2f());
    else
        std::cout << "Light: " << id << " not found." << std::endl;
}

void asSetAmbientColor(int r, int g, int b)
{
    g_scriptingScene->setAmbientColor(sf::Color(r, g, b));
}

float asGetLightIntensity(const std::string& id)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        return light->getIntensity();

    std::cout << "Light: " << id << " not found." << std::endl;

    return 0.0f;
}

void asSetLightIntensity(const std::string& id, float intensity)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        light->setIntensity(math::clamp(intensity, 0.0f, 1.0f));
    else
        std::cout << "Light: " << id << " not found." << std::endl;
}

float asGetLightRadius(const std::string& id)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        return light->getRadius();

    std::cout << "Light: " << id << " not found." << std::endl;

    return 0.0f;
}

void asSetLightRadius(const std::string& id, float radius)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        light->setRadius(radius);
    else
        std::cout << "Light: " << id << " not found." << std::endl;
}

float asGetLightAngle(const std::string& id)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
    {
        SpotLight* spotLight = static_cast<SpotLight*>(light);
        
        return spotLight->getAngle();
    }

    std::cout << "Light: " << id << " not found." << std::endl;

    return 0.0f;
}

void asSetLightAngle(const std::string& id, float angle)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
    {
        SpotLight* spotLight = static_cast<SpotLight*>(light);
        
        spotLight->setAngle(angle);
    }
    else
        std::cout << "Light: " << id << " not found." << std::endl;
}

void asSetLightState(const std::string& id, bool on)
{
    Light* light = g_scriptingScene->getLightById(id);

    if (light)
        light->setOn(on);
    else
        std::cout << "Light: " << id << " not found." << std::endl;
}

/// Entities ///
Vec2 asGetEntityPosition(const std::string& id)
{
    Entity* entity = g_scriptingScene->getEntityById(id);
    
    if (entity)
        return Vec2(entity->getPosition());
    
    std::cout << "Entity: " << id << " not found." << std::endl;
    
    return Vec2();
}

void asSetEntityPosition(const std::string& id, Vec2& pos)
{
    Entity* entity = g_scriptingScene->getEntityById(id);
    
    if (entity)
        entity->setPosition(pos.toVector2f());
    else
        std::cout << "Entity: " << id << " not found." << std::endl;
}

/// Player ///
void asAddPlayer(const std::string& id, Vec2& pos)
{
    g_scriptingScene->addEntity(new Player(g_scriptingScene, id, pos.toVector2f()));
}

/// Zombies ///
void asAddZombie(const std::string& id, Vec2& pos)
{
    g_scriptingScene->addEntity(new Zombie(g_scriptingScene, id, pos.toVector2f()));
}

/// Particles ///
void asLoadParticleSystem(const std::string& filename)
{
    g_scriptingScene->loadParticleSystem(filename);
}

void asFireParticleSystem(const std::string& name, Vec2& pos)
{
    g_scriptingScene->fireParticleSystem(name, pos.toVector2f());
}

/// Sounds ///
void asPlayMusic(const std::string& filename)
{
    MM.GetResource(filename)->Play();
}

void asStopMusic(const std::string& filename)
{
    MM.GetResource(filename)->Stop();
}

void asPlaySound(const std::string& filename, float volume, float pitch)
{
    g_AudioPlayer.playSound(filename, volume, pitch);
}

void ScriptInterface::registerProperties(asIScriptEngine* engine)
{
    
}

void ScriptInterface::registerFunctions(asIScriptEngine* engine)
{
    /// General ///
    engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(asPrint, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("float lerp(float value, float start, float end)", asFUNCTIONPR(asLerp, (float, float, float), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vec2 getWindowSize()", asFUNCTION(asGetWindowSize), asCALL_CDECL);

    /// Input ///
    engine->RegisterGlobalFunction("bool isKeyDown(const string &in)", asFUNCTIONPR(asIsKeyDown, (const std::string&), bool), asCALL_CDECL);

    /// Random numbers ///
    engine->RegisterGlobalFunction("int rand(int min, int max)", asFUNCTIONPR(asRandInt, (int, int), int), asCALL_CDECL);
    engine->RegisterGlobalFunction("float rand(float min, float max)", asFUNCTIONPR(asRandFloat, (float, float), float), asCALL_CDECL);

    /// Lights ///
    engine->RegisterGlobalFunction("void addSpotLight(const string &in, Vec2 &in, float intensity, float radius, int r, int g, int b, float angle, float openAngle)", asFUNCTIONPR(asAddSpotLight, (const std::string&, Vec2&, float, float, int, int, int, float, float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void addPointLight(const string &in, Vec2 &in, float intensity, float radius, int r, int g, int b, int quality)", asFUNCTIONPR(asAddPointLight, (const std::string&, Vec2&, float, float, int, int, int, int), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setAmbientColor(int r, int g, int b)", asFUNCTIONPR(asSetAmbientColor, (int, int, int), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("Vec2 getLightPosition(const string &in)", asFUNCTIONPR(asGetLightPosition, (const std::string&), Vec2), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setLightPosition(const string &in, Vec2 &in)", asFUNCTIONPR(asSetLightPosition, (const std::string&, Vec2&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("float getLightIntensity(const string &in)", asFUNCTIONPR(asGetLightIntensity, (const std::string&), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setLightIntensity(const string &in, float intensity)", asFUNCTIONPR(asSetLightIntensity, (const std::string&, float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("float getLightRadius(const string &in)", asFUNCTIONPR(asGetLightRadius, (const std::string&), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setLightRadius(const string &in, float radius)", asFUNCTIONPR(asSetLightRadius, (const std::string&, float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setLightAngle(const string &in, float angle)", asFUNCTIONPR(asSetLightAngle, (const std::string&, float), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("float getLightAngle(const string &in)", asFUNCTIONPR(asGetLightAngle, (const std::string&), float), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setLightState(const string &in, bool on)", asFUNCTIONPR(asSetLightState, (const std::string&, bool), void), asCALL_CDECL);

    /// Entities ///
    engine->RegisterGlobalFunction("Vec2 getEntityPosition(const string &in)", asFUNCTIONPR(asGetEntityPosition, (const std::string&), Vec2), asCALL_CDECL);
    engine->RegisterGlobalFunction("void setEntityPosition(const string &in, Vec2 &in)", asFUNCTIONPR(asSetEntityPosition, (const std::string&, Vec2&), void), asCALL_CDECL);

    /// Player ///
    engine->RegisterGlobalFunction("void addPlayer(const string &in, Vec2 &in)", asFUNCTIONPR(asAddPlayer, (const std::string&, Vec2&), void), asCALL_CDECL);


    /// Zombie ///
    engine->RegisterGlobalFunction("void addZombie(const string &in, Vec2 &in)", asFUNCTIONPR(asAddZombie, (const std::string&, Vec2&), void), asCALL_CDECL);

    /// Particles ///
    engine->RegisterGlobalFunction("void loadParticleSystem(const string &in)", asFUNCTIONPR(asLoadParticleSystem, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void fireParticleSystem(const string &in, Vec2 &in)", asFUNCTIONPR(asFireParticleSystem, (const std::string&, Vec2&), void), asCALL_CDECL);

    /// Sounds ///
    engine->RegisterGlobalFunction("void playMusic(const string &in)", asFUNCTIONPR(asPlayMusic, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void stopMusic(const string &in)", asFUNCTIONPR(asStopMusic, (const std::string&), void), asCALL_CDECL);
    engine->RegisterGlobalFunction("void playSound(const string &in, float volume, float pitch)", asFUNCTIONPR(asPlaySound, (const std::string&, float, float), void), asCALL_CDECL);
}

void ScriptInterface::registerTypes(asIScriptEngine* engine)
{
    /// Vec2
    engine->RegisterObjectType("Vec2", sizeof(Vec2), asOBJ_VALUE | asOBJ_POD | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(asVec2Constructor), asCALL_CDECL_OBJFIRST);
    engine->RegisterObjectBehaviour("Vec2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(asVec2InitConstructor), asCALL_CDECL_OBJFIRST);

    engine->RegisterObjectProperty("Vec2", "float x", offsetof(Vec2, x));
    engine->RegisterObjectProperty("Vec2", "float y", offsetof(Vec2, y));

    engine->RegisterObjectMethod("Vec2", "Vec2 opAdd(const Vec2 &in)", asMETHODPR(Vec2, operator+, (const Vec2&), Vec2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2 opSub(const Vec2 &in)", asMETHODPR(Vec2, operator-, (const Vec2&), Vec2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2 opMul(float)", asMETHODPR(Vec2, operator*, (float), Vec2), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2 opDiv(float)", asMETHODPR(Vec2, operator/, (float), Vec2), asCALL_THISCALL);

    engine->RegisterObjectMethod("Vec2", "Vec2& opAddAssign(const Vec2 &in)", asMETHODPR(Vec2, operator+=, (const Vec2&), Vec2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2& opSubAssign(const Vec2 &in)", asMETHODPR(Vec2, operator-=, (const Vec2&), Vec2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2& opMulAssign(float)", asMETHODPR(Vec2, operator*=, (float), Vec2&), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "Vec2& opDivAssign(float)", asMETHODPR(Vec2, operator/=, (float), Vec2&), asCALL_THISCALL);

    engine->RegisterObjectMethod("Vec2", "float length()", asMETHOD(Vec2, getLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "float lengthSquared()", asMETHOD(Vec2, getLengthSquared), asCALL_THISCALL);
    engine->RegisterObjectMethod("Vec2", "void normalize()", asMETHOD(Vec2, normalize), asCALL_THISCALL);
}
