#pragma once
#include "Expression.h"
#include "MathExpression.h"

namespace or2l
{
enum class MathExpressionOperatorTypes
{
    EQUAL,
    GREATER_EQUAL,
    GREATER,
    LESS_EQUAL,
    LESS
};

enum class ObjectiveExpressionOperatorTypes
{
    MINIMIZE,
    MAXIMIZE
};

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

class ObjectiveWrapper
{
  public:
    ObjectiveWrapper(ObjectiveExpressionOperatorTypes type, const Expression &expr) : type(type), expr(expr)
    {
    }
    virtual ~ObjectiveWrapper() = default;

  private:
    ObjectiveExpressionOperatorTypes type = ObjectiveExpressionOperatorTypes::MINIMIZE;
    Expression expr = {};
};
} // namespace or2l