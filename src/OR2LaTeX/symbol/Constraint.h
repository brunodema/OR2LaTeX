#pragma once
#include "MathExpression.h"

namespace or2l
{
class Constraint : public SymbolComponent
{
  public:
    Constraint(const base_types::RegexString &_name, const MathExpression &_math_expression)
        : SymbolComponent(_name, SymbolType::CONSTRAINT), math_expression(_math_expression)
    {
    }

    ~Constraint() override = default;

  private:
    MathExpression math_expression;
};
} // namespace or2l
