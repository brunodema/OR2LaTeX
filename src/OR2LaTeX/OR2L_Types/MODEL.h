#pragma once
#include <string>
#include <map>
#include "REGEX_STRING.h"
#include "SYMBOL_COMPONENT.h"
#include "VARIABLE.h"
#include "VARIABLE_SET.h"
#include "INDEX.h"
#include "CONSTRAINT.h"

namespace OR2L
{
    class MODEL
    {
    public:
        MODEL(const REGEX_STRING& name, std::initializer_list<INDEX> indexes, std::initializer_list<VARIABLE> variables, std::initializer_list<CONSTRAINT> constraints) :
            name_(name)
        {
            for (auto&& index : indexes)
            {
                symbol_map_.insert_or_assign(index.GetName(), index);
            }
            for (auto&& variable : variables)
            {
                symbol_map_.insert_or_assign(variable.GetName(), variable);
            }
            for (auto&& constraint : constraints)
            {
                symbol_map_.insert_or_assign(constraint.GetName(), constraint);
            }
        }
        MODEL(const REGEX_STRING& name) : name_(name) {}
        virtual ~MODEL() {}

        void AddVariable(const VARIABLE& var)
        {
            symbol_map_.insert_or_assign(var.GetName(), var);
        }

        void RemoveVariable(const VARIABLE& var)
        {
            symbol_map_.erase(var.GetName());
        }

        void ExtractIndexes(const VARIABLE& var)
        {
            for (auto&& index : var.GetIndexes())
            {
                symbol_map_.insert_or_assign(index.GetName(), index);
            }
        }

        void AddIndex(const INDEX& index)
        {
            symbol_map_.insert_or_assign(index.GetName(), index);
        }

        void RemoveIndex(const INDEX& index)
        {
            symbol_map_.erase(index.GetName());
        }

        void AddVariableSet(const VARIABLE_SET& var_set)
        {
            symbol_map_.insert_or_assign(var_set.GetName(), var_set);
        }

        void RemoveVariableSet(const VARIABLE_SET& var_set)
        {
            symbol_map_.erase(var_set.GetName());
        }

        void AddConstraint(const CONSTRAINT& constraint)
        {
            symbol_map_.insert_or_assign(constraint.GetName(), constraint);
        }

        void RemoveConstraint(const CONSTRAINT& constraint)
        {
            symbol_map_.erase(constraint.GetName());
        }


    private:
        REGEX_STRING name_ = "";
        std::map<REGEX_STRING, SYMBOL_COMPONENT> symbol_map_ = {};
    };
} // namespace OR2L