#pragma once
#include "SYMBOL_STRING.h"
#include "SYMBOL_TYPE.h"

namespace OR2L
{
	class SYMBOL_COMPONENT
	{
	public:
		SYMBOL_COMPONENT(const std::string& str, const SYMBOL_TYPE& type) : name_(str), type_(type) {}
		virtual ~SYMBOL_COMPONENT() {}

		virtual inline SYMBOL_STRING GetName() const { return name_; }
		virtual inline void SetName(const std::string& str) { name_ = str; }

	protected:
		SYMBOL_STRING name_;
		SYMBOL_TYPE type_;
	};
} // namespace OR2L
