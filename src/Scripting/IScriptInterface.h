#ifndef ISCRIPTINTERFACE_H_INCLUDED
#define ISCRIPTINTERFACE_H_INCLUDED

#include <angelscript.h>

class IScriptInterface
{
public:
    virtual void registerProperties(asIScriptEngine* engine) = 0;
    virtual void registerFunctions(asIScriptEngine* engine) = 0;
    virtual void registerTypes(asIScriptEngine* engine) = 0;
};

#endif // ISCRIPTINTERFACE_H_INCLUDED
