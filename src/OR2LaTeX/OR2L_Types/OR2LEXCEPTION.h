#pragma once
#include <exception>
#include <sstream>
#include <map>

namespace OR2L
{
    enum class EXCEPTION_TYPE
    {
        ERR_SYMBOLSTRING_INVALIDCHAR,
        ERR_INDEX_BOUNDS,
        ERR_EXPRESSION_VARNOTFOUND
    };

    static std::map<EXCEPTION_TYPE, std::string_view> EXCEPTION_TEXT =
    {
        {EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR, "The specified string contains an invalid character."},
        {EXCEPTION_TYPE::ERR_INDEX_BOUNDS, "The specified lower bound is higher than the upper bound."}
    };

    class OR2LEXCEPTION : public std::exception
    {
    public:
        OR2LEXCEPTION(const std::exception e, std::string message = "")
        {
            buffer_ << e.what() << " | " << message << "\n";
        }

        OR2LEXCEPTION(EXCEPTION_TYPE type, std::string message = "")
        {
            buffer_ << "OR2L Exception | " << OR2L::EXCEPTION_TEXT.at(type) << "\n";
        }

        OR2LEXCEPTION(std::string message = "")
        {
            buffer_ << "OR2L Exception | " << message << "\n";
        }

        OR2LEXCEPTION(const OR2LEXCEPTION&) = default;
        OR2LEXCEPTION(OR2LEXCEPTION&&) = default;
        virtual OR2LEXCEPTION& operator=(const OR2LEXCEPTION&) = default;
        virtual OR2LEXCEPTION& operator=(OR2LEXCEPTION&&) = default;
        virtual ~OR2LEXCEPTION() = default;

    private:
        inline static std::stringstream buffer_;
    };

} // namespace OR2L