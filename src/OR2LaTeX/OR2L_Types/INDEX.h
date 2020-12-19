#pragma once
#include <string>

namespace OR2L
{
	class INDEX
	{
	public:
		INDEX(int lb, int ub, const std::string& name) : 
			_lb(lb), 
			_ub(ub), 
			_name(name) 
		{
			if (ub - lb <= 0) { throw; }
		}

		INDEX() {}

		INDEX(const INDEX&) = default;
		INDEX(INDEX&&) noexcept = default;
		virtual INDEX& operator=(const INDEX&) = default;
		virtual INDEX& operator=(INDEX&&) = default;
		virtual ~INDEX() = default;

		bool operator==(const INDEX& B) const
		{
			return this->_lb == B._lb &&
				this->_ub == B._ub &&
				this->_name == B._name;
		}

		int GetSize() const { return _ub - _lb; }

		std::string _name = "";
	private:
		int _lb = 0;
		int _ub = 0;
	};
}


