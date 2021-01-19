#include "RegexString.h"

namespace or2l {
RegexString::RegexString(const std::string& str) : std::string(str) {
  if (ContainsInvalidChar())
    throw std::invalid_argument(
        "The provided string does not respect the regex rule provided.(" +
        *this + ")");
}
RegexString::RegexString(const char* charp) : std::string(charp) {
  if (ContainsInvalidChar())
    throw std::invalid_argument(
        "The provided string does not respect the regex rule provided.(" +
        *this + ")");
}
};  // namespace or2l