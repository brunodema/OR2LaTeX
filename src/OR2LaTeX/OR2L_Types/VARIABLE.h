#pragma once
#include "INDEX.h"
#include "VARIABLE_TYPE.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <stdarg.h>

namespace OR2L
{
	class VARIABLE
	{
	public:
		friend struct std::hash<VARIABLE>;

		VARIABLE(const std::string& name = "", VARIABLE_TYPE var_type = VARIABLE_TYPE::CONTINUOUS,
			const std::initializer_list<INDEX> indexes = {}) : name_(name)
		{
			for (auto&& index : indexes)
			{
				indexes_.insert(std::pair<std::string, INDEX>(index.GetName(), index));
			}
		}

		VARIABLE(const VARIABLE&) = default;
		VARIABLE(VARIABLE&&) = default;
		virtual VARIABLE& operator=(const VARIABLE&) = default;
		virtual VARIABLE& operator=(VARIABLE&&) = default;
		virtual ~VARIABLE() = default;

		bool operator==(const VARIABLE& B) const
		{
			return this->name_ == B.name_ && this->indexes_ == B.indexes_;
		}

		inline std::size_t GetNumberOfIndexes() { return indexes_.size(); }
		inline INDEX GetIndex(const std::string& key) const { return indexes_.at(key); }
		std::vector<size_t> GetIndexSizes() const;
		inline std::string GetName() const { return name_; }
		inline void SetName(const std::string& str) { name_ = str; }

	private:
		std::unordered_map<std::string, INDEX> indexes_ = {};
		VARIABLE_TYPE variable_type_ = VARIABLE_TYPE::CONTINUOUS;
		std::string name_ = "";
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
