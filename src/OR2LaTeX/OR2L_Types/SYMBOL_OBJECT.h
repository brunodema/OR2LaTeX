#pragma once
#include <string>
#include <variant>
#include "INDEX.h"
#include "VARIABLE.h"
#include "VARIABLE_SET.h"
#include "SYMBOL_TYPE.h"
#include "SYMBOL_STRING.h"

namespace OR2L
{
    class SYMBOL_OBJECT
    {
    public:
        SYMBOL_OBJECT(const SYMBOL_STRING& name, const SYMBOL_TYPE type, const std::variant < INDEX, VARIABLE, VARIABLE_SET> object)
            : name_(name),
            type_(type),
            object_(object) {}

        SYMBOL_OBJECT(const SYMBOL_OBJECT&) = default;
        SYMBOL_OBJECT(SYMBOL_OBJECT&&) = default;
        virtual SYMBOL_OBJECT& operator=(const SYMBOL_OBJECT&) = default;
        virtual SYMBOL_OBJECT& operator=(SYMBOL_OBJECT&&) = default;
        virtual ~SYMBOL_OBJECT() = default;
    private:
        std::string name_;
        SYMBOL_TYPE type_;
        std::variant<INDEX, VARIABLE, VARIABLE_SET> object_;
    };
} // namespace OR2L