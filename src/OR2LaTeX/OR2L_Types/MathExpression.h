#pragma once
#include "Expression.h"
#include "ExpressionOperatorTypes.h"

namespace or2l {
class MathExpression {
 public:
  MathExpression(const Expression& lhs, const ExpressionOperatorTypes eq_type,
                 const Expression& rhs)
      : lhs_(lhs), eq_type_(eq_type), rhs_(rhs) {}
  virtual ~MathExpression() = default;

 private:
  Expression lhs_ = Expression(1.00);
  Expression rhs_ = Expression(1.00);
  ExpressionOperatorTypes eq_type_ = ExpressionOperatorTypes::EQUAL;
};

}  // namespace or2l