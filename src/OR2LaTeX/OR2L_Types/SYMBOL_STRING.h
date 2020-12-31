#pragma once
#include <string>
#include <regex>
#include <cassert>
#include "OR2LEXCEPTION.h"

namespace OR2L
{
    class SYMBOL_STRING : public std::string // considering that I only want to implement a minor check on the constructor of the base class, this does not seem so wrong
    {
    public:
        SYMBOL_STRING(const std::string& str) : std::string(str)
        {
            if (ContainsInvalidChar())
                throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR);
        }
        SYMBOL_STRING(const char* charp) : std::string(charp)
        {
            if (ContainsInvalidChar())
                throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR);
        }
        virtual ~SYMBOL_STRING() {}

    private:
        std::regex filter_ = std::regex("[^a-zA-Z0-9]");

        bool ContainsInvalidChar() const
        {
            return std::regex_search(*this, filter_);
        }
    };
} // namespace OR2L
