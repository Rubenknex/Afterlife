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

    void Script::prepareFunction(const std::string& name)
    {
        m_FuncId = m_Module->GetFunctionIdByName(name.c_str());
        m_Manager->m_Context->Prepare(m_FuncId);
    }

    void Script::setArgInt(int arg, int value)
    {
        m_Manager->m_Context->SetArgDWord(arg, value);
    }

    void Script::setArgFloat(int arg, float value)
    {
        m_Manager->m_Context->SetArgFloat(arg, value);
    }

    void Script::setArgDouble(int arg, double value)
    {
        m_Manager->m_Context->SetArgDouble(arg, value);
    }

    void Script::setArgObject(int arg, void* value)
    {
        m_Manager->m_Context->SetArgObject(arg, value);
    }

    void Script::executeFunction()
    {
        if (m_FuncId != -1)
            m_Manager->m_Context->Execute();

        m_FuncId = -1;
    }
}
