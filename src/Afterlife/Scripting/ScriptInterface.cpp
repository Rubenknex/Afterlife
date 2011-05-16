#include "ScriptInterface.h"

#include <SFML/Audio.hpp>

#include "../EntityFactory.h"
#include "../EntityManager.h"
#include "../LightManager.h"
#include "../ResourceManager.h"

namespace al
{
    World* g_World = NULL;

    void setWorld(World* world)
    {
        g_World = world;
    }

    void asPrint(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    void asAddZombie(float x, float y)
    {
        g_World->getEntityManager()->add(EntityFactory::createZombie(g_World, sf::Vector2f(x, y)));
    }

    void asPlayMusic(const std::string& filename)
    {
        MM.GetResource(filename)->Play();
    }

    void asSetAmbientColor(int r, int g, int b)
    {
        g_World->getLightManager()->setAmbientColor(sf::Color(r, g, b));
    }

    int asRandInt(int min, int max)
    {
        return sf::Randomizer::Random(min, max);
    }

    float asRandFloat(float min, float max)
    {
        return sf::Randomizer::Random(min, max);
    }

    void asSetLightIntensity(const std::string& name, float intensity)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setIntensity(intensity);
    }

    void asSetLightRadius(const std::string& name, float radius)
    {
        boost::shared_ptr<Light> light = g_World->getLightManager()->getLightByName(name);

        if (light)
            light->setRadius(radius);
    }

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

    Vec2 asGetPlayerPosition()
    {
        return Vec2(g_World->getEntityManager()->getById(g_World->getPlayerId())->GetPosition());
    }

    int asGetZombieCount()
    {
        return g_World->getEntityManager()->queryType(Entity::ZOMBIE).size();
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
        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(asPrint, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void addZombie(float x, float y)", asFUNCTIONPR(asAddZombie, (float, float), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void playMusic(const string &in)", asFUNCTIONPR(asPlayMusic, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void setAmbientColor(int r, int g, int b)", asFUNCTIONPR(asSetAmbientColor, (int, int, int), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("int rand(int min, int max)", asFUNCTIONPR(asRandInt, (int, int), int), asCALL_CDECL);
        engine->RegisterGlobalFunction("float rand(float min, float max)", asFUNCTIONPR(asRandFloat, (float, float), float), asCALL_CDECL);
        engine->RegisterGlobalFunction("void setLightIntensity(const string &in, float intensity)", asFUNCTIONPR(asSetLightIntensity, (const std::string&, float), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void setLightRadius(const string &in, float radius)", asFUNCTIONPR(asSetLightRadius, (const std::string&, float), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("Vec2 getPlayerPosition()", asFUNCTION(asGetPlayerPosition), asCALL_CDECL);
        engine->RegisterGlobalFunction("int getZombieCount()", asFUNCTION(asGetZombieCount), asCALL_CDECL);
    }

    void ScriptInterface::registerObjects(asIScriptEngine* engine)
    {
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
