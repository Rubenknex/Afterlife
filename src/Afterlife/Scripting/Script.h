#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <angelscript.h>
#include "../../AngelScript/scriptbuilder.h"

#include "ScriptManager.h"

namespace al
{
    class Script
    {
        public:
            Script(ScriptManager* manager, const std::string& moduleName);
            ~Script();

            void loadSection(const std::string& filename);
            void build();
            void executeFunction(const std::string& name);
            void executeFunctionFloat(const std::string& name, float arg0);

        private:
            ScriptManager* m_Manager;
            asIScriptModule* m_Module;

            bool m_Compiled;
    };
}

#endif // SCRIPT_H_INCLUDED
