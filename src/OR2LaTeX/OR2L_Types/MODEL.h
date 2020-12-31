#pragma once
#include <string>
#include <map>
#include "SYMBOL_STRING.h"
#include "SYMBOL_COMPONENT.h"

namespace OR2L
{
    class MODEL
    {
    public:
        MODEL(SYMBOL_STRING& name) : name_(name) {}
        virtual ~MODEL() {}

    private:
        SYMBOL_STRING name_ = "";
        std::map<std::string, SYMBOL_COMPONENT> symbol_map_ = {};
    };
} // namespace OR2L