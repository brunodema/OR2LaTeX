#pragma once

#include "Expression.h"
#include "OperatorTypes.h"
namespace or2l
{
class ObjectiveWrapper
{
  public:
    ObjectiveWrapper(ObjectiveExpressionOperatorTypes type, const Expression &expr) : type_(type), expr_(expr)
    {
    }
    virtual ~ObjectiveWrapper() = default;

  private:
    ObjectiveExpressionOperatorTypes type_ = ObjectiveExpressionOperatorTypes::MINIMIZE;
    Expression expr_ = {};
};
} // namespace or2l
