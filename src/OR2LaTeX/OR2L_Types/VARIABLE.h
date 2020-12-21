#pragma once
#include "INDEX.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <stdarg.h>

namespace OR2L
{
	class VARIABLE
	{
	public:
		VARIABLE(const std::initializer_list<INDEX> indexes = {}, std::string name = "") : _name(name)
		{
			for (auto &index : indexes)
			{
				_index_map.insert(std::pair<std::string, INDEX>(index._name, index));
			}
		}

		VARIABLE(const VARIABLE &) = default;
		VARIABLE(VARIABLE &&) = default;
		virtual VARIABLE &operator=(const VARIABLE &) = default;
		virtual VARIABLE &operator=(VARIABLE &&) = default;
		virtual ~VARIABLE() = default;

		bool operator==(const VARIABLE &B) const
		{
			return this->_name == B._name && this->_index_map == B._index_map;
		}

		inline std::size_t GetNumberOfIndexes() { return _index_map.size(); }
		inline INDEX Index(const std::string &key) const { return _index_map.at(key); }
		std::vector<size_t> GetIndexSizes() const;
		inline std::string Name() const { return _name; }

		friend std::vector<INDEX> GetIndexes(const VARIABLE &B);

	private:
		std::string _name = "";
		std::unordered_map<std::string, INDEX> _index_map;
	};
} // namespace OR2L
