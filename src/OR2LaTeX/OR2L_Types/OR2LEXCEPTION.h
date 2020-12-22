#pragma once
#include <exception>
#include <sstream>

namespace OR2L
{
    class OR2LEXCEPTION : public std::exception
    {
    public:
        OR2LEXCEPTION(const std::exception e, std::string message = "") : std::exception(e)
        {
            _buffer << e.what() << " | " << message << "\n";
        }

        //EXCEPTION() {}

        OR2LEXCEPTION(const OR2LEXCEPTION &) = default;
        OR2LEXCEPTION(OR2LEXCEPTION &&) = default;
        virtual OR2LEXCEPTION &operator=(const OR2LEXCEPTION &) = default;
        virtual OR2LEXCEPTION &operator=(OR2LEXCEPTION &&) = default;
        virtual ~OR2LEXCEPTION() = default;

    private:
        inline static std::stringstream _buffer;
    };

} // namespace OR2L