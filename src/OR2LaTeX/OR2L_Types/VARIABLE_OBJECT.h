#pragma once
#include "VARIABLE.h"

#include <string>

namespace OR2L
{
	class VARIABLE_OBJECT
	{
	public:
		VARIABLE_OBJECT(const VARIABLE& variable, std::optional<std::initializer_list<int>> index_values, std::optional<std::string> name) :
			_variable(variable),
			_index_values(index_values),
			_name(name) 
		{
			if (index_values.has_value() && name.has_value()) { _is_fully_initiazed = true; }
		}

		VARIABLE_OBJECT() {}

		VARIABLE_OBJECT(const VARIABLE_OBJECT&) = default;
		VARIABLE_OBJECT(VARIABLE_OBJECT&&) = default;
		virtual VARIABLE_OBJECT& operator=(const VARIABLE_OBJECT&) = default;
		virtual VARIABLE_OBJECT& operator=(VARIABLE_OBJECT&&) = default;
		virtual ~VARIABLE_OBJECT() = default;

	private:
		bool _is_fully_initiazed = false;

		VARIABLE _variable = {};
		std::optional<std::vector<int>> _index_values = std::nullopt;
		std::optional<std::string> _name = std::nullopt;
	};
}


