#pragma once
#include "REGEX_STRING.h"
#include "SYMBOL_TYPE.h"
#include <memory>

namespace OR2L
{
	class SYMBOL_COMPONENT
	{
	public:
		SYMBOL_COMPONENT(const std::string& str, const SYMBOL_TYPE& type) : name_(str), type_(type) {}
		virtual ~SYMBOL_COMPONENT() {}

		//virtual std::unique_ptr<SYMBOL_COMPONENT> operator()();
		virtual inline REGEX_STRING GetName() const { return name_; }
		virtual inline void SetName(const std::string& str) { name_ = str; }

	protected:
		REGEX_STRING name_;
		SYMBOL_TYPE type_;
	};
} // namespace OR2L
