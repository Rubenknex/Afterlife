#include "ScriptInterface.h"

#include <SFML/Audio.hpp>

#include "../EntityFactory.h"
#include "../EntityManager.h"
#include "../LightManager.h"
#include "../ParticleManager.h"
#include "../ResourceManager.h"
#include "../PointLight.h"
#include "../AudioPlayer.h"
#include "../SpotLight.h"

namespace al
{
    World* g_World = NULL;

    void setWorld(World* world)
    {
        g_World = world;
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

    Vec2 asGetWindowSize()
    {
        return Vec2((float)g_Window->GetWidth(), (float)g_Window->GetHeight());
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
    void lightError(const std::string& name)
    {
        std::cout << "Light: " << name << " not found." << std::endl;
    }

    void asAddSpotLight(const std::string& name, Vec2& pos, float intensity, float radius, int r, int g, int b, float angle, float openAngle)
    {
        boost::shared_ptr<Light> light(new SpotLight(name, pos.toVector2f(), intensity, radius, sf::Color(r, g, b), angle, openAngle));
        g_World->getLightManager()->addLight(light);
    }

    void asAddPointLight(const std::string& name, Vec2& pos, float intensity, float radius, int r, int g, int b, int quality)
    {
        boost::shared_ptr<Light> light(new PointLight(name, pos.toVector2f(), intensity, radius, sf::Color(r, g, b), quality));
        g_World->getLightManager()->addLight(light);
    }

    Vec2 asGetLightPosition(const std::string& name)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            return light->getPosition();

        lightError(name);

        return Vec2();
    }

    void asSetLightPosition(const std::string& name, Vec2& pos)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setPosition(pos.toVector2f());
        else
            lightError(name);
    }

    void asSetAmbientColor(int r, int g, int b)
    {
        g_World->getLightManager()->setAmbientColor(sf::Color(r, g, b));
    }

    float asGetLightIntensity(const std::string& name)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            return light->getIntensity();

        lightError(name);

        return 0.0f;
    }

    void asSetLightIntensity(const std::string& name, float intensity)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setIntensity(clamp(intensity, 0.0f, 1.0f));
        else
            lightError(name);
    }

    float asGetLightRadius(const std::string& name)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            return light->getRadius();

        lightError(name);

        return 0.0f;
    }

    void asSetLightRadius(const std::string& name, float radius)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setRadius(radius);
        else
            lightError(name);
    }

    void asSetLightAngle(const std::string& name, float angle)
    {
        boost::shared_ptr<SpotLight> light = boost::static_pointer_cast<SpotLight>(g_World->getLightManager()->getLightByName(name));

        if (light)
            light->setAngle(angle);
        else
            lightError(name);
    }

    void asSetLightState(const std::string& name, bool on)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setOn(on);
        else
            lightError(name);
    }

    /// Player ///
    Vec2 asGetPlayerPosition()
    {
        return Vec2(g_World->getEntityManager()->getById(g_World->getPlayerId())->GetPosition());
    }

    /// Zombies ///
    void asAddZombie(float x, float y)
    {
        g_World->getEntityManager()->add(EntityFactory::createZombie(g_World, sf::Vector2f(x, y)));
    }

    int asGetZombieCount()
    {
        return g_World->getEntityManager()->queryType(Entity::ZOMBIE).size();
    }

    /// Particles ///
    void asLoadParticleSystem(const std::string& filename, const std::string& name)
    {
        g_World->getParticleManager()->loadSystem(filename, name);
    }

    void asFireParticleSystem(const std::string& name, Vec2& pos)
    {
        g_World->getParticleManager()->fireSystem(name, pos.toVector2f());
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

    ScriptInterface::ScriptInterface()
    {

    }

    ScriptInterface::~ScriptInterface()
    {

    }

    void ScriptInterface::registerAll(asIScriptEngine* engine)
    {
        if (g_World == NULL)
        {
            std::cout << "Failed to register script interface, g_World is NULL." << std::endl;

            return;
        }

        registerObjects(engine);
        registerFunctions(engine);
    }

    void ScriptInterface::registerFunctions(asIScriptEngine* engine)
    {
        /// General ///
        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(asPrint, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("Vec2 getWindowSize()", asFUNCTION(asGetWindowSize), asCALL_CDECL);

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
        engine->RegisterGlobalFunction("void setLightState(const string &in, bool on)", asFUNCTIONPR(asSetLightState, (const std::string&, bool), void), asCALL_CDECL);

        /// Player ///
        engine->RegisterGlobalFunction("Vec2 getPlayerPosition()", asFUNCTION(asGetPlayerPosition), asCALL_CDECL);

        /// Zombie ///
        engine->RegisterGlobalFunction("void addZombie(float x, float y)", asFUNCTIONPR(asAddZombie, (float, float), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("int getZombieCount()", asFUNCTION(asGetZombieCount), asCALL_CDECL);

        /// Particles ///
        engine->RegisterGlobalFunction("void loadParticleSystem(const string &in, const string &in)", asFUNCTIONPR(asLoadParticleSystem, (const std::string&, const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void fireParticleSystem(const string &in, Vec2 &in)", asFUNCTIONPR(asFireParticleSystem, (const std::string&, Vec2&), void), asCALL_CDECL);

        /// Sounds ///
        engine->RegisterGlobalFunction("void playMusic(const string &in)", asFUNCTIONPR(asPlayMusic, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void stopMusic(const string &in)", asFUNCTIONPR(asStopMusic, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void playSound(const string &in, float volume, float pitch)", asFUNCTIONPR(asPlaySound, (const std::string&, float, float), void), asCALL_CDECL);
    }

    void ScriptInterface::registerObjects(asIScriptEngine* engine)
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
    }
}
