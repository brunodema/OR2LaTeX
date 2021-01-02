#pragma once
#include <string>
#include <regex>
#include <cassert>
#include "OR2LEXCEPTION.h"

namespace OR2L
{
    class REGEX_STRING : public std::string // considering that I only want to implement a minor check on the constructor of the base class, this does not seem so wrong
    {
    public:
        REGEX_STRING(const std::string& str) : std::string(str)
        {
            if (ContainsInvalidChar())
                throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR);
        }
        REGEX_STRING(const char* charp) : std::string(charp)
        {
            if (ContainsInvalidChar())
                throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR);
        }
        virtual ~REGEX_STRING() {}

    private:
        std::regex filter_ = std::regex("[^a-zA-Z0-9]");

        bool ContainsInvalidChar() const
        {
            return std::regex_search(*this, filter_);
        }
    };
} // namespace OR2L

template <>
struct std::hash<OR2L::REGEX_STRING>
{
    std::size_t operator()(const OR2L::REGEX_STRING& k) const
    {
        // changed it to be based on their names, which makes sense when thinking about the LaTeX implementation
        return std::hash<std::string>()(k);
    };
};
