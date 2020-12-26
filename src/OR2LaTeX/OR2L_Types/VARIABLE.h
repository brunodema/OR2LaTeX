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
		friend class std::hash<VARIABLE>;

		VARIABLE(const std::initializer_list<INDEX> indexes = {}, const std::string &name = "") : _name(name)

		{
			for (auto &&index : indexes)
			{
				_hash = 0;
				_indexes.insert(std::pair<std::string, INDEX>(index.GetName(), index));
			}
		}

		VARIABLE(const VARIABLE &) = default;
		VARIABLE(VARIABLE &&) = default;
		virtual VARIABLE &operator=(const VARIABLE &) = default;
		virtual VARIABLE &operator=(VARIABLE &&) = default;
		virtual ~VARIABLE() = default;

		bool operator==(const VARIABLE &B) const
		{
			return this->_name == B._name && this->_indexes == B._indexes;
		}

		inline std::size_t GetNumberOfIndexes() { return _indexes.size(); }
		inline INDEX GetIndex(const std::string &key) const { return _indexes.at(key); }
		std::vector<size_t> GetIndexSizes() const;
		inline std::string GetName() const { return _name; }
		inline void SetName(const std::string &str) { _name = str; }

	private:
		std::unordered_map<std::string, INDEX> _indexes;
		std::string _name = "";
		size_t _hash;
	};
} // namespace OR2L

template <>
struct std::hash<OR2L::VARIABLE>
{
	std::size_t operator()(const OR2L::VARIABLE &k) const
	{
		// a completelly terrible hasher - used only for scientific reasons (need to study more about this)
		size_t ret = 0;
		std::vector<size_t> hash_elements = {std::hash<std::string>()(k.GetName())};
		for (auto it = k._indexes.begin(); it != k._indexes.end(); ++it)
		{
			hash_elements.push_back(std::hash<std::string>()(it->first));
			hash_elements.push_back(std::hash<size_t>()(it->second.GetLB()));
			hash_elements.push_back(std::hash<size_t>()(it->second.GetUB()));
			hash_elements.push_back(std::hash<std::string>()(it->second.GetName()));
		}
		for (auto &&hash : hash_elements)
		{
			ret += hash << 1;
		}
		return ret;
	};
};
