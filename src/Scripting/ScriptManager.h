#ifndef SCRIPTMANAGER_H_INCLUDED
#define SCRIPTMANAGER_H_INCLUDED

#include <iostream>

#include <angelscript.h>
#include "../../AngelScript/scriptbuilder.h"
#include "../../AngelScript/scriptmath.h"
#include "../../AngelScript/scriptstdstring.h"

namespace al
{
    class ScriptInterface;

    class ScriptManager
    {
        friend class Script;

        public:
            ScriptManager();
            ~ScriptManager();

            void initialize();

        private:
            void messageCallBack(const asSMessageInfo* msg, void* param);

        private:
            CScriptBuilder m_Builder;

            asIScriptEngine* m_Engine;
            asIScriptContext* m_Context;

            ScriptInterface* m_Interface;
    };

    extern ScriptManager g_ScriptManager;
}

#endif // SCRIPTMANAGER_H_INCLUDED
