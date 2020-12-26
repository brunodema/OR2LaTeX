#pragma once
#include <string>
#include "OR2LEXCEPTION.h"

namespace OR2L
{
	class INDEX
	{
	public:
		INDEX(size_t lb, size_t ub, const std::string &name) : lb_(lb),
															   ub_(ub),
															   name_(name)
		{
			if (ub <= lb)
			{
				throw OR2LEXCEPTION(EXCEPTION_TYPE::ERR_INDEX_BOUNDS);
			}
		}

		INDEX() {}

		INDEX(const INDEX &) = default;
		INDEX(INDEX &&) = default;
		virtual INDEX &operator=(const INDEX &) = default;
		virtual INDEX &operator=(INDEX &&) = default;
		virtual ~INDEX() = default;

		bool operator==(const INDEX &B) const
		{
			return this->lb_ == B.lb_ &&
				   this->ub_ == B.ub_ &&
				   this->name_ == B.name_;
		}

		inline size_t GetUB() const { return ub_; }
		inline size_t GetLB() const { return lb_; }
		inline size_t GetSize() const { return ub_ - lb_; }
		inline std::string GetName() const { return name_; }

	private:
		size_t lb_ = 0;
		size_t ub_ = 0;
		std::string name_;
	};
} // namespace OR2L
