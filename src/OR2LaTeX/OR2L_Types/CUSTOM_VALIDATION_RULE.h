#pragma once
#include <optional>
#include <functional>

#include "VARIABLE.h"

namespace OR2L
{
	class CUSTOM_VALIDATION_RULE : public std::optional<std::function<bool(const VARIABLE&)>>
	{
	public:
		CUSTOM_VALIDATION_RULE() {}

		CUSTOM_VALIDATION_RULE(const CUSTOM_VALIDATION_RULE&) = default;
		CUSTOM_VALIDATION_RULE(CUSTOM_VALIDATION_RULE&&) = default;
		virtual CUSTOM_VALIDATION_RULE& operator=(const CUSTOM_VALIDATION_RULE&) = default;
		virtual CUSTOM_VALIDATION_RULE& operator=(CUSTOM_VALIDATION_RULE&&) = default;
		virtual ~CUSTOM_VALIDATION_RULE() = default;

		bool IsVariableValid(const VARIABLE& var) const
		{
			if (!this->has_value())
			{
				return true;
			}
			return this->value()(var);
		}
	};
} // namespace OR2L
