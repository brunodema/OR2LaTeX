#pragma once
#include <string>
#include <map>
#include "SYMBOL_OBJECT.h"
#include "SYMBOL_STRING.h"

namespace OR2L
{
    class MODEL
    {
    public:
        MODEL(SYMBOL_STRING& name) : name_(name) {}
        virtual ~MODEL() {}

    private:
        SYMBOL_STRING name_ = "";
        std::map<std::string, SYMBOL_OBJECT> symbol_map_ = {};
    };
} // namespace OR2L