#pragma once
#include "Exception.h"
#include <cassert>
#include <regex>
#include <string>

namespace or2l {
class RegexString
    : public std::string  // considering that I only want to implement a minor
                          // check on the constructor of the base class, this
                          // does not seem so wrong
{
 public:
  RegexString(const std::string& str) : std::string(str) {
    if (ContainsInvalidChar())
      throw Exception(ExceptionType::ERR_SYMBOLSTRING_INVALIDCHAR);
  }
  RegexString(const char* charp) : std::string(charp) {
    if (ContainsInvalidChar())
      throw Exception(ExceptionType::ERR_SYMBOLSTRING_INVALIDCHAR);
  }
  virtual ~RegexString() = default;

 private:
  std::regex filter_ = std::regex("[^a-zA-Z0-9]");

  [[nodiscard]] bool ContainsInvalidChar() const {
    return std::regex_search(*this, filter_);
  }
};
}  // namespace or2l

template <>
struct std::hash<or2l::RegexString> {
  std::size_t operator()(const or2l::RegexString& k) const {
    // changed it to be based on their names, which makes sense when thinking
    // about the LaTeX implementation
    return std::hash<std::string>()(k);
  };
};
