#pragma once

#include "Expression.h"
#include "OperatorTypes.h"
namespace or2l
{
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
