#pragma once
#include "INDEX.h"
#include "VARIABLE_TYPE.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <stdarg.h>

namespace OR2L
{
	class VARIABLE : public SYMBOL_COMPONENT
	{
	public:
		friend struct std::hash<VARIABLE>;

		VARIABLE(const std::string& name = "", VARIABLE_TYPE var_type = VARIABLE_TYPE::CONTINUOUS, const std::initializer_list<INDEX> indexes = {})
			: SYMBOL_COMPONENT(name, SYMBOL_TYPE::VARIABLE)
		{
			for (auto&& index : indexes)
			{
				indexes_.insert(std::pair<std::string, INDEX>(index.GetName(), index));
			}
		}
		virtual ~VARIABLE() {}

		bool operator==(const VARIABLE& B) const
		{
			return this->name_ == B.name_ && this->indexes_ == B.indexes_;
		}

		inline std::size_t GetNumberOfIndexes() { return indexes_.size(); }
		inline INDEX GetIndex(const std::string& key) const { return indexes_.at(key); }
		std::vector<size_t> GetIndexSizes() const;
		std::vector<INDEX> GetIndexes() const
		{
			std::vector<INDEX> ret;
			for (auto&& index : indexes_)
			{
				ret.push_back(index.second);
			}
			return ret;
		}

	private:
		std::unordered_map<std::string, INDEX> indexes_ = {};
		VARIABLE_TYPE variable_type_ = VARIABLE_TYPE::CONTINUOUS;
	};
} // namespace OR2L

template <>
struct std::hash<OR2L::VARIABLE>
{
	std::size_t operator()(const OR2L::VARIABLE& k) const
	{
		// changed it to be based on their names, which makes sense when thinking about the LaTeX implementation
		return std::hash<std::string>()(k.GetName());
	};
};
