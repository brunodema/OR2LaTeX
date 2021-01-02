#pragma once
#include <cmath>
#include <exception>
#include <map>
#include <sstream>

namespace or2l  // remake this to make each exception its own class, just like
                // the STL exceptions are coded
{
enum class EXCEPTION_TYPE {
  ERR_SYMBOLSTRING_INVALIDCHAR,
  ERR_INDEX_BOUNDS,
  ERR_EXPRESSION_VARNOTFOUND
};

static std::map<EXCEPTION_TYPE, std::string_view> EXCEPTION_TEXT = {
    {EXCEPTION_TYPE::ERR_SYMBOLSTRING_INVALIDCHAR,
     "The specified string contains an invalid character."},
    {EXCEPTION_TYPE::ERR_INDEX_BOUNDS,
     "The specified lower bound is higher than the upper bound."}};

class OR2LEXCEPTION : public std::exception {
 public:
  explicit OR2LEXCEPTION(const std::exception e, std::string message = "") {
    buffer_ << e.what() << " | " << message << "\n";
  }

  explicit OR2LEXCEPTION(EXCEPTION_TYPE type, std::string message = "") {
    buffer_ << "OR2L Exception | " << or2l::EXCEPTION_TEXT.at(type) << "\n";
  }

  explicit OR2LEXCEPTION(std::string message = "") {
    buffer_ << "OR2L Exception | " << message << "\n";
  }
  virtual ~OR2LEXCEPTION() = default;

 private:
  inline static std::stringstream buffer_;
};

}  // namespace or2l