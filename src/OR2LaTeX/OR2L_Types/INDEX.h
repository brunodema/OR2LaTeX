#pragma once
#include <string>
#include "OR2LEXCEPTION.h"
#include "SYMBOL_COMPONENT.h"

namespace OR2L
{
	class INDEX : public SYMBOL_COMPONENT
	{
	public:
		INDEX(const REGEX_STRING& name, const size_t lb, const size_t ub) :
			SYMBOL_COMPONENT(name, SYMBOL_TYPE::INDEX),
			lb_(lb),
			ub_(ub)
		{
			if (ub <= lb)
			{
				throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_INDEX_BOUNDS);
			}
		}
		virtual ~INDEX() {}

		bool operator==(const INDEX& B) const
		{
			return this->lb_ == B.lb_ &&
				this->ub_ == B.ub_ &&
				this->name_ == B.name_;
		}

		inline size_t GetUB() const { return ub_; }
		inline size_t GetLB() const { return lb_; }
		inline size_t GetSize() const { return ub_ - lb_; }

	private:
		size_t lb_ = 0;
		size_t ub_ = 0;
	};
} // namespace OR2L

template <>
struct std::hash<OR2L::INDEX>
{
	std::size_t operator()(const OR2L::INDEX& k) const
	{
		// changed it to be based on their names, which makes sense when thinking about the LaTeX implementation
		return std::hash<std::string>()(k.GetName());
	};
};