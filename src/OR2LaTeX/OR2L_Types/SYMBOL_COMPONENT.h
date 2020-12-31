#pragma once
#include "SYMBOL_STRING.h"

namespace OR2L
{
	class SYMBOL_COMPONENT
	{
	public:
		SYMBOL_COMPONENT(const std::string& str) : name_(str) {}

		SYMBOL_COMPONENT(const SYMBOL_COMPONENT&) = default;
		SYMBOL_COMPONENT(SYMBOL_COMPONENT&&) = default;
		virtual SYMBOL_COMPONENT& operator=(const SYMBOL_COMPONENT&) = default;
		virtual SYMBOL_COMPONENT& operator=(SYMBOL_COMPONENT&&) = default;
		virtual ~SYMBOL_COMPONENT() = default;

		virtual inline SYMBOL_STRING GetName() const { return name_; }
		virtual inline void SetName(const std::string& str) { name_ = str; }

	protected:
		SYMBOL_STRING name_;
	};
} // namespace OR2L
