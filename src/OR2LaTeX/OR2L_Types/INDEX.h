#pragma once
#include <string>

namespace OR2L
{
	class INDEX
	{
	public:
		INDEX(size_t lb, size_t ub, const std::string &name) : _lb(lb),
															   _ub(ub),
															   _name(name)
		{
			if (ub <= lb)
			{
				throw;
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
			return this->_lb == B._lb &&
				   this->_ub == B._ub &&
				   this->_name == B._name;
		}

		inline size_t GetUB() const { return _ub; }
		inline size_t GetLB() const { return _lb; }
		inline size_t GetSize() const { return _ub - _lb; }
		inline std::string GetName() const { return _name; }

	private:
		size_t _lb = 0;
		size_t _ub = 0;
		std::string _name;
	};
} // namespace OR2L
