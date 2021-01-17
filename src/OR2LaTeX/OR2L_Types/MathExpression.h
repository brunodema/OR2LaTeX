#pragma once
#include "Expression.h"
#include "OperatorTypes.h"

namespace or2l {
class MathExpression {
 public:
  MathExpression(const Expression& lhs,
                 const MathExpressionOperatorTypes eq_type,
                 const Expression& rhs)
      : lhs_(lhs), eq_type_(eq_type), rhs_(rhs) {}
  virtual ~MathExpression() = default;

 private:
  Expression lhs_ = Expression(0.00);
  Expression rhs_ = Expression(0.00);
  MathExpressionOperatorTypes eq_type_ = MathExpressionOperatorTypes::EQUAL;
};

}  // namespace or2l