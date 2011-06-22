#ifndef SCRIPTMANAGER_H_INCLUDED
#define SCRIPTMANAGER_H_INCLUDED

#include <iostream>

#include <angelscript.h>
#include "AngelScript/scriptbuilder.h"
#include "AngelScript/scriptmath.h"
#include "AngelScript/scriptstdstring.h"

class IScriptInterface;

class ScriptManager
{
    friend class Script;

public:
    ScriptManager();
    ~ScriptManager();

    void registerInterface(IScriptInterface* interface);

private:
    void messageCallBack(const asSMessageInfo* msg, void* param);

private:
    CScriptBuilder m_builder;

    asIScriptEngine* m_engine;
    asIScriptContext* m_context;
};

extern ScriptManager g_scriptManager;

#endif // SCRIPTMANAGER_H_INCLUDED
