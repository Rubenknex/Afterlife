#ifndef SCRIPTINTERFACE_H_INCLUDED
#define SCRIPTINTERFACE_H_INCLUDED

#include <angelscript.h>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "../World.h"

namespace al
{
    void setWorld(World* world);

    class ScriptInterface
    {
        public:
            ScriptInterface();
            ~ScriptInterface();

            void registerAll(asIScriptEngine* engine);
            void registerFunctions(asIScriptEngine* engine);
            void registerObjects(asIScriptEngine* engine);
    };

    extern World* g_World;
}

#endif // SCRIPTINTERFACE_H_INCLUDED
