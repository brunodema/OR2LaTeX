#pragma once
#include <string>
#include <regex>
#include "OR2LEXCEPTION.h"

namespace OR2L
{
    class SYMBOL_STRING : public std::string // deriviing from a base class seems to be a bad practice. Trnasform this into a 'trait' class
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

        SYMBOL_STRING(const SYMBOL_STRING&) = default;
        SYMBOL_STRING(SYMBOL_STRING&&) = default;
        virtual SYMBOL_STRING& operator=(const SYMBOL_STRING&) = default;
        virtual SYMBOL_STRING& operator=(SYMBOL_STRING&&) = default;
        virtual ~SYMBOL_STRING() = default;

    private:
        std::regex filter_ = std::regex("[^a-zA-Z0-9]"); // not owrking

        bool ContainsInvalidChar() const
        {
            return std::regex_search(*this, filter_);
        }
    };
} // namespace OR2L
