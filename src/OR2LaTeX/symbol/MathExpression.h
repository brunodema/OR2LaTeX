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
    MathExpression(const Expression &_lhs, const MathExpressionOperatorType _eq_type, const Expression &_rhs)
        : lhs(_lhs), rhs(_rhs), eq_type(_eq_type)
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
    ObjectiveExpression(ObjectiveExpressionOperatorType _type, const Expression &_expr) : type(_type), expr(_expr)
    {
    }
    virtual ~ObjectiveExpression() = default;

  private:
    ObjectiveExpressionOperatorType type = ObjectiveExpressionOperatorType::MINIMIZE;
    Expression expr = {};
};
} // namespace or2l