#include "Script.h"

    Script::Script(ScriptManager* manager, const std::string& moduleName) :
        m_manager(manager)
    {
        m_manager->m_builder.StartNewModule(m_manager->m_engine, moduleName.c_str());
        m_module = m_manager->m_engine->GetModule(moduleName.c_str());
    }

    Script::~Script()
    {

    }

    void Script::loadSection(const std::string& filename)
    {
        m_manager->m_builder.AddSectionFromFile(filename.c_str());
    }

    void Script::build()
    {
        m_manager->m_builder.BuildModule();

        m_compiled = true;
    }

    void Script::prepareFunction(const std::string& name)
    {
        m_funcId = m_module->GetFunctionIdByName(name.c_str());
        m_manager->m_context->Prepare(m_funcId);
    }

    void Script::setArgInt(int arg, int value)
    {
        m_manager->m_context->SetArgDWord(arg, value);
    }

    void Script::setArgFloat(int arg, float value)
    {
        m_manager->m_context->SetArgFloat(arg, value);
    }

    void Script::setArgDouble(int arg, double value)
    {
        m_manager->m_context->SetArgDouble(arg, value);
    }

    void Script::setArgObject(int arg, void* value)
    {
        m_manager->m_context->SetArgObject(arg, value);
    }

    void Script::executeFunction()
    {
        if (m_funcId != -1)
            m_manager->m_context->Execute();

        m_funcId = -1;
    }
