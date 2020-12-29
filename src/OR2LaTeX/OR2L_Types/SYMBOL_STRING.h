#pragma once
#include <string>
#include <regex>
#include "OR2LEXCEPTION.h"

namespace OR2L
{
    class SYMBOL_STRING : public std::string
    {
    public:
        SYMBOL_STRING(const std::string&)
        {
            if (ContainsInvalidChar(*this))
                throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR);
        }

        SYMBOL_STRING(const SYMBOL_STRING&) = default;
        SYMBOL_STRING(SYMBOL_STRING&&) = default;
        virtual SYMBOL_STRING& operator=(const SYMBOL_STRING&) = default;
        virtual SYMBOL_STRING& operator=(SYMBOL_STRING&&) = default;
        virtual ~SYMBOL_STRING() = default;

    private:
        std::regex filter_ = std::regex("[-!#@ºª\\=-¨$%^&*()_+|~=`{}[]:\";'<>?,.\\/]");

        constexpr bool ContainsInvalidChar(const std::string& str)
        {
            return std::regex_match(str, filter_);
        }
    }
} // namespace OR2L
