#pragma once
#include "VARIABLE.h"
#include <functional>
#include <optional>


namespace or2l {
class CustomValidationRule
    : public std::optional<std::function<bool(const VARIABLE&)>> {
 public:
  CustomValidationRule() = default;
  virtual ~CustomValidationRule() = default;

  [[nodiscard]] bool IsVariableValid(const VARIABLE& var) const {
    if (!this->has_value()) {
      return true;
    }
    return this->value()(var);
  }
};
}  // namespace or2l
