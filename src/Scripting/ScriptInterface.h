#ifndef SCRIPTINTERFACE_H_INCLUDED
#define SCRIPTINTERFACE_H_INCLUDED

#include <angelscript.h>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "IScriptInterface.h"
#include "../World.h"

    void setWorld(World* world);

    class ScriptInterface : public IScriptInterface
    {
        public:
            void registerProperties(asIScriptEngine* engine);
            void registerFunctions(asIScriptEngine* engine);
            void registerTypes(asIScriptEngine* engine);
    };

    extern World* g_World;

#endif // SCRIPTINTERFACE_H_INCLUDED
