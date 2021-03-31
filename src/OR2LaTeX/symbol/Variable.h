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

    template <typename H> friend H AbslHashValue(H _h, const IndexedObject &_obj);
    inline bool operator==(const IndexedObject &_obj) const
    {
        return this->GetIndexes() == _obj.GetIndexes();
    }

    virtual Index GetIndex(const base_types::RegexString &_index_name)
    {
        return indexes[_index_name];
    }
    virtual std::vector<Index> GetIndexes() const
    {
        std::vector<Index> ret{};
        for (const auto &pair : indexes)
        {
            ret.push_back(pair.second);
        }
        return ret;
    }
    virtual std::vector<std::size_t> GetIndexSizes() const
    {
        std::vector<std::size_t> ret{};
        for (const auto &pair : indexes)
        {
            ret.push_back(pair.second.GetSize());
        }
        return ret;
    }

    // private:
    std::unordered_map<base_types::RegexString, Index> indexes = {};
};

template <typename H> H AbslHashValue(H _h, const or2l::IndexedObject &_obj)
{
    return H::combine(std::move(_h), _obj.GetIndexes());
}

class Constant : public Symbol, public IndexedObject
{
  public:
    Constant() : Symbol("", SymbolType::CONSTANT){};
    Constant(const base_types::RegexString &_name, std::initializer_list<Index> _indexes = {})
        : Symbol(_name, SymbolType::CONSTANT), IndexedObject(_indexes){};

    inline bool operator==(const Constant &_other) const
    {
        return this->name_ == _other.name_ && this->indexes == _other.indexes;
    }
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
             std::initializer_list<Index> _indexes = {})
        : Symbol(_name, SymbolType::VARIABLE), IndexedObject(_indexes), variable_type_(_var_type)
    {
        for (const auto &index : _indexes)
        {
            indexes[(index.GetName())] = index;
        }
    };
    ~Variable() override = default;

    template <typename H> friend H AbslHashValue(H _h, const Variable &_var);
    inline bool operator==(const Variable &_other) const
    {
        return this->name_ == _other.name_ && this->indexes == _other.indexes;
    }

    VariableType GetVariableType() const
    {
        return variable_type_;
    };

  private:
    VariableType variable_type_ = VariableType::CONTINUOUS;
};

template <typename H> H AbslHashValue(H _h, const or2l::Variable &_var)
{
    return H::combine(std::move(_h), _var.name_, _var.GetIndexes());
}
} // namespace or2l
