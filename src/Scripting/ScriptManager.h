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

    void initialize();
    void registerInterface(IScriptInterface* interface);

private:
    void messageCallBack(const asSMessageInfo* msg, void* param);

private:
    CScriptBuilder m_Builder;

    asIScriptEngine* m_Engine;
    asIScriptContext* m_Context;
};

extern ScriptManager g_ScriptManager;

#endif // SCRIPTMANAGER_H_INCLUDED
