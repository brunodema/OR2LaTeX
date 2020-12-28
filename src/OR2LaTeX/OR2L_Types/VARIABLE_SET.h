#pragma once
#include "VARIABLE.h"
#include "VARIABLE_OBJECT.h"
#include "CUSTOM_VALIDATION_RULE.h"
#include "Vecxd.h"

#include <functional>
#include <optional>

using namespace DEMALIB::BASE_TYPES;

namespace OR2L
{
	class VARIABLE_SET
	{
	public:
		/**
		 * @brief Construct an object which holds information related to a specified variable template, and all its associated creation/validation rules.
		 *
		 * @param variable Variable template to be used.
		 * @param custom_rule Optional rule to be applied when creating the variable objects. It must be a 'bool(const VARIABLE&)' style lambda.
		 */
		VARIABLE_SET(const VARIABLE& variable, CUSTOM_VALIDATION_RULE custom_rule = {}) : custom_rule_(custom_rule),
			template_variable_(variable)
		{
			variable_objects = Vecxd<VARIABLE_OBJECT>(variable.GetIndexSizes(), VARIABLE_OBJECT(variable));
		}

		VARIABLE_SET(const VARIABLE_SET&) = default;
		VARIABLE_SET(VARIABLE_SET&&) = default;
		virtual VARIABLE_SET& operator=(const VARIABLE_SET&) = default;
		virtual VARIABLE_SET& operator=(VARIABLE_SET&&) = default;
		virtual ~VARIABLE_SET() = default;

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
