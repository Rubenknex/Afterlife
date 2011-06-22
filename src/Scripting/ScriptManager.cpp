#include "ScriptManager.h"

#include "IScriptInterface.h"

ScriptManager g_scriptManager;

ScriptManager::ScriptManager()
{
    m_engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

    m_engine->SetMessageCallback(asMETHOD(ScriptManager, messageCallBack), this, asCALL_THISCALL);

    RegisterScriptMath(m_engine);
    RegisterStdString(m_engine);

    m_context = m_engine->CreateContext();
}

ScriptManager::~ScriptManager()
{
    m_context->Release();
    m_engine->Release();
}

void ScriptManager::registerInterface(IScriptInterface* interface)
{
    interface->registerTypes(m_engine);
    interface->registerProperties(m_engine);
    interface->registerFunctions(m_engine);
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
