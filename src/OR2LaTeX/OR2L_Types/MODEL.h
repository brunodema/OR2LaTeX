#pragma once
#include <string>
#include <map>
#include "SYMBOL_OBJECT.h"

namespace OR2L
{
    class MODEL
    {
    public:
        MODEL(const std::string& name) : name_(name) {}

        MODEL(const MODEL&) = default;
        MODEL(MODEL&&) = default;
        virtual MODEL& operator=(const MODEL&) = default;
        virtual MODEL& operator=(MODEL&&) = default;
        virtual ~MODEL() = default;

    private:
        std::string name_ = "";
        std::map<std::string, SYMBOL_OBJECT> symbol_map_ = {};
    }
} // namespace OR2L