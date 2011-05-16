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

            void prepareFunction(const std::string& name);
            void setArgInt(int arg, int value);
            void setArgFloat(int arg, float value);
            void setArgDouble(int arg, double value);
            void setArgObject(int arg, void* value);
            void executeFunction();

        private:
            ScriptManager* m_Manager;
            asIScriptModule* m_Module;

            bool m_Compiled;

            int m_FuncId;
    };
}

#endif // SCRIPT_H_INCLUDED
