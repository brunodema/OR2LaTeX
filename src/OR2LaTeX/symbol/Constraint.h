#pragma once
#include "MathExpression.h"

namespace or2l
{
class Constraint : public SymbolComponent
{
  public:
    Constraint(const base_types::RegexString &name, const MathExpression &math_expression)
        : SymbolComponent(name, SymbolType::CONSTRAINT), math_expression(math_expression)
    {
    }

    ~Constraint() override = default;

  private:
    MathExpression math_expression;
};
} // namespace or2l
