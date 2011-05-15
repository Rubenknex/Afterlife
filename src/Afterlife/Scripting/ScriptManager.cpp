#include "ScriptManager.h"

namespace al
{
    ScriptManager g_ScriptManager;

    ScriptManager::ScriptManager()
    {

    }

    ScriptManager::~ScriptManager()
    {
        m_Context->Release();
        m_Engine->Release();
    }

    void ScriptManager::initialize()
    {
        m_Engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

        m_Engine->SetMessageCallback(asMETHOD(ScriptManager, messageCallBack), this, asCALL_THISCALL);

        RegisterScriptMath(m_Engine);
        RegisterStdString(m_Engine);
        m_Interface.registerAll(m_Engine);

        m_Context = m_Engine->CreateContext();
    }

    void ScriptManager::messageCallBack(const asSMessageInfo* msg, void* param)
    {
        const char* type = "ERR";
            if (msg->type == asMSGTYPE_WARNING)
                type = "WARN";
            else if (msg->type == asMSGTYPE_INFORMATION)
                type = "INFO";

            std::cout << msg->section << "(" << msg->row << "," << msg->col << ") : " << type << " : " << msg->message << std::endl;
    }
}