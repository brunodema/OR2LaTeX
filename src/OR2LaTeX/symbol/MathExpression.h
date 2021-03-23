#pragma once
#include "Expression.h"
#include "OperatorTypes.h"

namespace or2l
{
class MathExpression
{
  public:
    MathExpression(const Expression &lhs, const MathExpressionOperatorTypes eq_type, const Expression &rhs)
        : lhs(lhs), rhs(rhs), eq_type(eq_type)
    {
    }
    virtual ~MathExpression() = default;

  private:
    Expression lhs = Expression(0.00);
    Expression rhs = Expression(0.00);
    MathExpressionOperatorTypes eq_type = MathExpressionOperatorTypes::EQUAL;
};

} // namespace or2l