#pragma once
#include <cmath>
#include <exception>
#include <map>
#include <sstream>
#include <string_view>

namespace or2l // remake this to make each exception its own class, just like
               // the STL exceptions are coded
{
enum class ExceptionType
{
    ERR_SYMBOLSTRING_INVALIDCHAR,
    ERR_INDEX_BOUNDS,
    ERR_EXPRESSION_VARNOTFOUND,
    ERR_MODEL_NULLPTRSOLVER
};

static std::map<ExceptionType, std::string_view> EXCEPTION_TEXT = {
    {ExceptionType::ERR_SYMBOLSTRING_INVALIDCHAR, "The specified string contains an invalid character."},
    {ExceptionType::ERR_INDEX_BOUNDS, "The specified lower bound is higher than the upper bound."},
    {ExceptionType::ERR_MODEL_NULLPTRSOLVER, "The underlying solver pointer is equal to 'nullptr'. Did you forget to "
                                             "define a solver first?"}};

class Exception : public std::exception
{
  public:
    explicit Exception(const std::exception &_e, const std::string &_message = "")
    {
        buffer << _e.what() << " | " << _message << "\n";
    }

    explicit Exception(ExceptionType _type)
    {
        buffer << "OR2L Exception | " << or2l::EXCEPTION_TEXT.at(_type) << "\n";
    }

    explicit Exception(const std::string &_message = "")
    {
        buffer << "OR2L Exception | " << _message << "\n";
    }
    ~Exception() override = default;

  private:
    inline static std::stringstream buffer;
};

} // namespace or2l