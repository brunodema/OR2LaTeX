#pragma once
#include <string>
#include <map>
#include "SYMBOL_STRING.h"
#include "SYMBOL_COMPONENT.h"
#include "VARIABLE.h"

namespace OR2L
{
    class MODEL
    {
    public:
        MODEL(SYMBOL_STRING& name) : name_(name) {}
        virtual ~MODEL() {}

        void AddVariable(const VARIABLE& var)
        {
            symbol_map_.insert_or_assign(var.GetName(), var);
        }

        void ExtractIndexes(const VARIABLE& var)
        {
            for (auto&& index : var.GetIndexes())
            {
                symbol_map_.insert_or_assign(index.GetName(), index);
            }
        }

    private:
        SYMBOL_STRING name_ = "";
        std::map<SYMBOL_STRING, SYMBOL_COMPONENT> symbol_map_ = {};
    };
} // namespace OR2L