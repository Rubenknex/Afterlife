#include "ScriptInterface.h"

#include <SFML/Audio.hpp>

#include "../EntityFactory.h"
#include "../EntityManager.h"
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

    class vec2
    {
        public:
            vec2() : x(0.0f), y(0.0f) { }
            vec2(float x, float y) : x(x), y(y) { }

        public:
            float x;
            float y;
    };

    static void asVec2DefaultConstructor(vec2* self)
    {
        new(self) vec2();
    }

    static void asVec2InitConstructor(vec2* self, float x, float y)
    {
        new(self) vec2(x, y);
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

        registerFunctions(engine);
        registerObjects(engine);
    }

    void ScriptInterface::registerFunctions(asIScriptEngine* engine)
    {
        engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTIONPR(asPrint, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void addZombie(float x, float y)", asFUNCTIONPR(asAddZombie, (float, float), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void playMusic(const string &in)", asFUNCTIONPR(asPlayMusic, (const std::string&), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("void setAmbientColor(int r, int g, int b)", asFUNCTIONPR(asSetAmbientColor, (int, int, int), void), asCALL_CDECL);
        engine->RegisterGlobalFunction("int rand(int min, int max)", asFUNCTIONPR(asRandInt, (int, int), int), asCALL_CDECL);
        engine->RegisterGlobalFunction("float rand(float min, float max)", asFUNCTIONPR(asRandFloat, (float, float), float), asCALL_CDECL);
    }

    void ScriptInterface::registerObjects(asIScriptEngine* engine)
    {

    }
}
