#ifndef SCRIPTINTERFACE_H_INCLUDED
#define SCRIPTINTERFACE_H_INCLUDED

#include <angelscript.h>
#include <iostream>

#include "IScriptInterface.h"

class Scene;

void setScriptingScene(Scene* scene);

class ScriptInterface : public IScriptInterface
{
public:
    void registerProperties(asIScriptEngine* engine);
    void registerFunctions(asIScriptEngine* engine);
    void registerTypes(asIScriptEngine* engine);
};

extern Scene* g_scriptingScene;

#endif // SCRIPTINTERFACE_H_INCLUDED
