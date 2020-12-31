#pragma once
#include <string>
#include <map>
#include "SYMBOL_OBJECT.h"
#include "SYMBOL_STRING.h"

namespace OR2L
{
    class MODEL : SYMBOL_COMPONENT
    {
    public:
        MODEL(SYMBOL_STRING& name) :
            SYMBOL_COMPONENT(name) {}
        virtual ~MODEL() {}
    private:
        std::map<std::string, SYMBOL_OBJECT> symbol_map_ = {};
    };
} // namespace OR2L