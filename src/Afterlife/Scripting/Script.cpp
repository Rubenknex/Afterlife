#include "Script.h"

namespace al
{
    Script::Script(ScriptManager* manager, const std::string& moduleName) :
        m_Manager(manager)
    {
        m_Manager->m_Builder.StartNewModule(m_Manager->m_Engine, moduleName.c_str());
        m_Module = m_Manager->m_Engine->GetModule(moduleName.c_str());
    }

    Script::~Script()
    {

    }

    void Script::loadSection(const std::string& filename)
    {
        m_Manager->m_Builder.AddSectionFromFile(filename.c_str());
    }

    void Script::build()
    {
        m_Manager->m_Builder.BuildModule();

        m_Compiled = true;
    }

    void Script::executeFunction(const std::string& name)
    {
        if (m_Compiled)
        {
            int funcId = m_Module->GetFunctionIdByName(name.c_str());
            m_Manager->m_Context->Prepare(funcId);
            m_Manager->m_Context->Execute();
        }
    }

    void Script::executeFunctionFloat(const std::string& name, float arg0)
    {
        if (m_Compiled)
        {
            int funcId = m_Module->GetFunctionIdByName(name.c_str());
            m_Manager->m_Context->Prepare(funcId);
            m_Manager->m_Context->SetArgFloat(0, arg0);
            m_Manager->m_Context->Execute();
        }
    }
}
