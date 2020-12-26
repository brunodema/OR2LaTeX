#pragma once
#include "VARIABLE.h"
#include "VARIABLE_OBJECT.h"
#include "CUSTOM_VALIDATION_RULE.h"
#include "Vecxd.h"

#include <functional>
#include <optional>

namespace OR2L
{
	class VARIABLE_SET
	{
	public:
		VARIABLE_SET(const VARIABLE &variable, CUSTOM_VALIDATION_RULE custom_rule = {}) : custom_rule_(custom_rule),
																						  template_variable_(variable)
		{
			variable_objects = DEMALIB::BASE_TYPES::Vecxd<VARIABLE_OBJECT>({variable.GetIndexSizes()}, VARIABLE_OBJECT(variable, std::nullopt, std::nullopt));
		}

		VARIABLE_SET(const VARIABLE_SET &) = default;
		VARIABLE_SET(VARIABLE_SET &&) = default;
		virtual VARIABLE_SET &operator=(const VARIABLE_SET &) = default;
		virtual VARIABLE_SET &operator=(VARIABLE_SET &&) = default;
		virtual ~VARIABLE_SET() = default;

		void PopulateSet();

	private:
		CUSTOM_VALIDATION_RULE custom_rule_;
		VARIABLE template_variable_;
		DEMALIB::BASE_TYPES::Vecxd<VARIABLE_OBJECT> variable_objects;

		bool CheckVariableFromCustomRule(const VARIABLE &var) const { return custom_rule_.IsVariableValid(var); }
	};
} // namespace OR2L
