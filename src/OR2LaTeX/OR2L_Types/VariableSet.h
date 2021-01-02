#pragma once
#include "CustomValidationRule.h"
#include "RegexString.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableObject.h"
#include "Vecxd.h"
#include <functional>
#include <optional>

namespace or2l {
class VariableSet : public SymbolComponent {
 public:
  /**
   * @brief Construct an object which holds information related to a specified
   * variable template, and all its associated creation/validation rules.
   * @param name Name of the variable set (must abide by the rules of
   * 'RegexString').
   * @param variable Variable template to be used.
   * @param custom_rule Optional rule to be applied when creating the variable
   * objects. It must be a 'bool(const Variable&)' style lambda.
   */
  VariableSet(const RegexString& name, const Variable& variable,
              const CustomValidationRule& custom_rule = {})
      : SymbolComponent(name, SymbolType::VARIABLE_SET),
        template_variable_(variable),
        custom_rule_(custom_rule_) {}
  ~VariableSet() override = default;
  /**
   * @brief Creates all variables within the set, following the specified
   * variable template and custom rules.
   *
   */
  void PopulateSet();

 private:
  CustomValidationRule custom_rule_;
  Variable template_variable_;
  or2l::base_types::Vecxd<VariableObject> variable_objects_;

  /**
   * @brief Executes a custom validation rule to determine if current variable
   * is valid or not.
   *
   * @param var Variable to be examined by the custom function (argument of the
   * lambda).
   * @return true Current variable is valid.
   * @return false Current variable is not valid.
   */
  inline bool CheckVariableFromCustomRule(const Variable& var) const {
    return custom_rule_.IsVariableValid(var);
  }
};
}  // namespace or2l
