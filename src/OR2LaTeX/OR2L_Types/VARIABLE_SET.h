#pragma once
#include "VARIABLE.h"
#include "VARIABLE_OBJECT.h"
#include "CUSTOM_VALIDATION_RULE.h"
#include "../../BaseTypesLib/Vecxd.h"

#include <functional>
#include <optional>

namespace OR2L
{
	class VARIABLE_SET
	{
	public:
		VARIABLE_SET(const VARIABLE& variable, CUSTOM_VALIDATION_RULE custom_rule = {}) :
			_custom_rule(custom_rule),
			_variable(variable)
		{
			_variables = DEMALIB::BASE_TYPES::Vecxd<VARIABLE_OBJECT>({ variable.GetIndexSizes() }, VARIABLE_OBJECT(variable, std::nullopt, std::nullopt));
		}

		VARIABLE_SET(const VARIABLE_SET&) = default;
		VARIABLE_SET(VARIABLE_SET&&) = default;
		virtual VARIABLE_SET& operator=(const VARIABLE_SET&) = default;
		virtual VARIABLE_SET& operator=(VARIABLE_SET&&) = default;
		virtual ~VARIABLE_SET() = default;

		void PopulateSet();
	private:
		CUSTOM_VALIDATION_RULE _custom_rule;
		VARIABLE _variable;
		DEMALIB::BASE_TYPES::Vecxd<VARIABLE_OBJECT> _variables;

		bool CheckVariableFromCustomRule(const VARIABLE& var) const { return _custom_rule.IsVariableValid(var); }
	};
}


