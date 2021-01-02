#pragma once
#include "MathExpression.h"

namespace or2l {
class Constraint : public SymbolComponent {
 public:
  Constraint(const RegexString& name, const MathExpression& math_expression)
      : SymbolComponent(name, SymbolType::CONSTRAINT),
        math_expression_(math_expression) {}

  ~Constraint() override = default;

 private:
  MathExpression math_expression_;
};
}  // namespace or2l
