#pragma once
#include "VARIABLE.h"
#include <unordered_map>

namespace OR2L
{
	class VARIABLE_OBJECT // redo the association with indexes
	{
	public:
		VARIABLE_OBJECT(const VARIABLE& variable) :
			template_variable_(variable),
			index_values_() {}

		VARIABLE_OBJECT() {}

		VARIABLE_OBJECT(const VARIABLE_OBJECT&) = default;
		VARIABLE_OBJECT(VARIABLE_OBJECT&&) = default;
		virtual VARIABLE_OBJECT& operator=(const VARIABLE_OBJECT&) = default;
		virtual VARIABLE_OBJECT& operator=(VARIABLE_OBJECT&&) = default;
		virtual ~VARIABLE_OBJECT() = default;

	private:
		VARIABLE template_variable_ = {};
		std::unordered_map<INDEX, size_t> index_values_ = {};
	};
} // namespace OR2L
