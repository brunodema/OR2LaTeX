#pragma once
#include "VARIABLE.h"
#include <functional>
#include <optional>


namespace or2l {
class CUSTOM_VALIDATION_RULE
    : public std::optional<std::function<bool(const VARIABLE&)>> {
 public:
  CUSTOM_VALIDATION_RULE() {}
  virtual ~CUSTOM_VALIDATION_RULE() {}

  bool IsVariableValid(const VARIABLE& var) const {
    if (!this->has_value()) {
      return true;
    }
    return this->value()(var);
  }
};
}  // namespace or2l
