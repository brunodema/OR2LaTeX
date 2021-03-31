#pragma once
#include "Index.h"
#include "SymbolComponent.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace or2l
{
class IndexedObject
{
  public:
    IndexedObject() = default;
    IndexedObject(std::initializer_list<Index> _indexes)
    {
        for (const auto &index : _indexes)
        {
            indexes[index.GetName()] = index;
        }
    }

    inline bool operator==(const IndexedObject &_obj) const
    {
        return this->indexes == _obj.indexes;
    }

    virtual Index GetIndex(const base_types::RegexString &_index_name)
    {
        return indexes[_index_name];
    }
    virtual std::vector<Index> GetIndexes() const
    {
        std::vector<Index> ret(indexes.size());
        for (const auto &pair : indexes)
        {
            ret.push_back(pair.second);
        }
        return ret;
    }
    virtual std::vector<std::size_t> GetIndexSizes() const
    {
        std::vector<std::size_t> ret(indexes.size());
        for (const auto &pair : indexes)
        {
            ret.push_back(pair.second.GetSize());
        }
        return ret;
    }

    // private:
    std::unordered_map<base_types::RegexString, Index> indexes = {};
};

class Constant : public Symbol
{
  public:
    Constant() : Symbol("", SymbolType::CONSTANT){};
    Constant(double coeff) : Symbol("", SymbolType::CONSTANT){};
};

enum class VariableType
{
    CONTINUOUS,
    INTEGER,
    BINARY
};

class Variable : public Symbol, public IndexedObject
{
  public:
    Variable() : Symbol("", SymbolType::VARIABLE){};
    Variable(const base_types::RegexString &_name, VariableType _var_type = VariableType::CONTINUOUS,
             std::initializer_list<Index> _indexes = {});
    ~Variable() override = default;

    template <typename H> friend H AbslHashValue(H _h, const Variable &_var);

    inline bool operator==(const Variable& _other) const
    {
        return this->name_ == _other.name_ && this->indexes == _other.indexes;
    }

    VariableType GetVariableType() const;
    std::vector<std::vector<size_t>> GetAllIndexCombinations() const;

  private:
    VariableType variable_type_ = VariableType::CONTINUOUS;
};
} // namespace or2l

template <typename H> H or2l::AbslHashValue(H _h, const or2l::Variable &_var)
{
    return H::combine(std::move(_h), _var.name_);
}