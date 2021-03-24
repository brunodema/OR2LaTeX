#pragma once
#include "Expression.h"
#include "MathExpression.h"

namespace or2l
{
enum class MathExpressionOperatorType
{
    EQUAL,
    GREATER_EQUAL,
    GREATER,
    LESS_EQUAL,
    LESS
};

enum class ObjectiveExpressionOperatorType
{
    MINIMIZE,
    MAXIMIZE
};

class MathExpression
{
  public:
    MathExpression(const Expression &lhs, const MathExpressionOperatorType eq_type, const Expression &rhs)
        : lhs(lhs), rhs(rhs), eq_type(eq_type)
    {
    }
    virtual ~MathExpression() = default;

  private:
    Expression lhs = Expression(0.00);
    Expression rhs = Expression(0.00);
    MathExpressionOperatorType eq_type = MathExpressionOperatorType::EQUAL;
};

class ObjectiveExpression
{
  public:
    ObjectiveExpression(ObjectiveExpressionOperatorType type, const Expression &expr) : type(type), expr(expr)
    {
    }
    virtual ~ObjectiveExpression() = default;

  private:
    ObjectiveExpressionOperatorType type = ObjectiveExpressionOperatorType::MINIMIZE;
    Expression expr = {};
};
} // namespace or2l