#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <angelscript.h>
#include "AngelScript/scriptbuilder.h"

#include "ScriptManager.h"

    /// Script manager a single AngelScript script module.
    class Script
    {
        public:
            Script(ScriptManager* manager, const std::string& moduleName);
            ~Script();

            /// Add a file into the script.
            void loadSection(const std::string& filename);
            /// Compile the script.
            void build();

            /// Prepares a function, call this when you want to call a script function.
            void prepareFunction(const std::string& name);

            /// Set the arguments of the script function.
            void setArgInt(int arg, int value);
            void setArgFloat(int arg, float value);
            void setArgDouble(int arg, double value);
            void setArgObject(int arg, void* value);

            /// Execute the script function.
            void executeFunction();

        private:
            ScriptManager* m_Manager;
            asIScriptModule* m_Module;

            bool m_Compiled;

            int m_FuncId;
    };

#endif // SCRIPT_H_INCLUDED
