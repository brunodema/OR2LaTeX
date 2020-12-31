#pragma once
#include "VARIABLE.h"
#include "VARIABLE_OBJECT.h"
#include "CUSTOM_VALIDATION_RULE.h"
#include "SYMBOL_COMPONENT.h"
#include "SYMBOL_STRING.h"
#include "Vecxd.h"

#include <functional>
#include <optional>

using namespace DEMALIB::BASE_TYPES;

namespace OR2L
{
	class VARIABLE_SET : SYMBOL_COMPONENT
	{
	public:
		/**
		 * @brief Construct an object which holds information related to a specified variable template, and all its associated creation/validation rules.
		 * @param name Name of the variable set (must abide by the rules of 'SYMBOL_STRING').
		 * @param variable Variable template to be used.
		 * @param custom_rule Optional rule to be applied when creating the variable objects. It must be a 'bool(const VARIABLE&)' style lambda.
		 */
		VARIABLE_SET(const SYMBOL_STRING& name, const VARIABLE& variable, CUSTOM_VALIDATION_RULE custom_rule = {}) :
			SYMBOL_COMPONENT(name),
			template_variable_(variable),
			custom_rule_(custom_rule_) {}

		/**
		 * @brief Creates all variables within the set, following the specified variable template and custom rules.
		 *
		 */
		void PopulateSet();

	private:
		CUSTOM_VALIDATION_RULE custom_rule_;
		VARIABLE template_variable_;
		Vecxd<VARIABLE_OBJECT> variable_objects;

		/**
		* @brief Executes a custom validation rule to determine if current variable is valid or not.
		*
		* @param var Variable to be examined by the custom function (argument of the lambda).
		* @return true Current variable is valid.
		* @return false Current variable is not valid.
		*/
		inline bool CheckVariableFromCustomRule(const VARIABLE& var) const { return custom_rule_.IsVariableValid(var); }
	};
} // namespace OR2L
