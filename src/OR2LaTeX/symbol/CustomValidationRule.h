#pragma once
#include "Variable.h"
#include <functional>
#include <optional>

namespace or2l
{
class CustomValidationRule : public std::optional<std::function<bool(const Variable &)>>
{
  public:
    CustomValidationRule() = default;
    virtual ~CustomValidationRule() = default;

    [[nodiscard]] inline bool IsVariableValid(const Variable &var) const
    {
        if (!this->has_value())
        {
            return true;
        }
        return this->value()(var);
    }
};
} // namespace or2l
