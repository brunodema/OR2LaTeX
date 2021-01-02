#pragma once
#include "CUSTOM_VALIDATION_RULE.h"
#include "REGEX_STRING.h"
#include "SYMBOL_COMPONENT.h"
#include "VARIABLE.h"
#include "VARIABLE_OBJECT.h"
#include "Vecxd.h"
#include <functional>
#include <optional>

using namespace or2l::base_types;

namespace or2l {
class VARIABLE_SET : public SYMBOL_COMPONENT {
 public:
  /**
   * @brief Construct an object which holds information related to a specified
   * variable template, and all its associated creation/validation rules.
   * @param name Name of the variable set (must abide by the rules of
   * 'REGEX_STRING').
   * @param variable Variable template to be used.
   * @param custom_rule Optional rule to be applied when creating the variable
   * objects. It must be a 'bool(const VARIABLE&)' style lambda.
   */
  VARIABLE_SET(const REGEX_STRING& name, const VARIABLE& variable,
               const CustomValidationRule& custom_rule = {})
      : SYMBOL_COMPONENT(name, SYMBOL_TYPE::VARIABLE_SET),
        template_variable_(variable),
        custom_rule_(custom_rule_) {}
  virtual ~VARIABLE_SET() {}
  /**
   * @brief Creates all variables within the set, following the specified
   * variable template and custom rules.
   *
   */
  void PopulateSet();

 private:
  CustomValidationRule custom_rule_;
  VARIABLE template_variable_;
  Vecxd<VARIABLE_OBJECT> variable_objects_;

  /**
   * @brief Executes a custom validation rule to determine if current variable
   * is valid or not.
   *
   * @param var Variable to be examined by the custom function (argument of the
   * lambda).
   * @return true Current variable is valid.
   * @return false Current variable is not valid.
   */
  inline bool CheckVariableFromCustomRule(const VARIABLE& var) const {
    return custom_rule_.IsVariableValid(var);
  }
};
}  // namespace or2l
