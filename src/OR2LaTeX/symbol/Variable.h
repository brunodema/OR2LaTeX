#pragma once
#include "Index.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace or2l
{
enum class VariableType
{
    CONTINUOUS,
    INTEGER,
    BINARY
};

class Variable : public SymbolComponent
{
  public:
    friend struct std::hash<Variable>;
    Variable() : SymbolComponent("", SymbolType::VARIABLE){};
    explicit Variable(const base_types::RegexString &_name, VariableType _var_type = VariableType::CONTINUOUS,
                      std::initializer_list<Index> _indexes = {});
    ~Variable() override = default;

    inline bool operator==(const Variable &_B) const
    {
        return this->name_ == _B.name_ && this->indexes_ == _B.indexes_;
    }
    inline bool operator<(const Variable &_A) const
    {
        return this->name_ < _A.name_;
    }

    std::size_t GetNumberOfIndexes();
    Index GetIndex(const base_types::RegexString &_key) const;
    std::vector<size_t> GetIndexSizes() const;
    std::vector<Index> GetIndexes() const;
    VariableType GetVariableType() const;
    std::vector<std::vector<size_t>> GetAllIndexCombinations() const;

  private:
    std::unordered_map<base_types::RegexString, Index> indexes_ = {};
    VariableType variable_type_ = VariableType::CONTINUOUS;
};
} // namespace or2l

template <> struct std::hash<or2l::Variable>
{
    std::size_t operator()(const or2l::Variable &_k) const
    {
        // changed it to be based on their names, which makes sense when thinking
        // about the LaTeX implementation
        return std::hash<std::string>()(_k.GetName());
    };
};
