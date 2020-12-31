#pragma once
#include "SYMBOL_STRING.h"

namespace OR2L
{
	class SYMBOL_COMPONENT
	{
	public:
		SYMBOL_COMPONENT(const std::string& str) : name_(str) {}
		virtual ~SYMBOL_COMPONENT() {}

		virtual inline SYMBOL_STRING GetName() const { return name_; }
		virtual inline void SetName(const std::string& str) { name_ = str; }

	protected:
		SYMBOL_STRING name_;
	};
} // namespace OR2L
