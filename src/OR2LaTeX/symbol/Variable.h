#pragma once
#include "Index.h"
#include "SymbolComponent.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace or2l
{
class IndexedSymbol : public Symbol
{
  public:
    IndexedSymbol() = default;
    IndexedSymbol(const base_types::RegexString &_str, const SymbolType &_type, std::initializer_list<Index> _indexes)
        : Symbol(_str, _type)
    {
        for (const auto &index : _indexes)
        {
            indexes[index.GetName()] = index;
        }
    }

    template <typename H> friend H AbslHashValue(H _h, const IndexedSymbol &_obj);
    virtual bool operator==(const IndexedSymbol &_other) const
    {
        return Compare(_other);
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

  protected:
    virtual bool Compare(const IndexedSymbol& _other) const
    {
        return this->name_ == _other.name_ && this->GetIndexes() == _other.GetIndexes();
    }
};

template <typename H> H AbslHashValue(H _h, const or2l::IndexedSymbol &_obj)
{
    return H::combine(std::move(_h), _obj.name_, _obj.GetIndexes());
}

class Constant : public IndexedSymbol
{
  public:
    Constant() : IndexedSymbol("", SymbolType::CONSTANT, {}){};
    Constant(const base_types::RegexString &_name, std::initializer_list<Index> _indexes = {})
        : IndexedSymbol(_name, SymbolType::CONSTANT, _indexes){};
    virtual ~Constant() = default;

    template <typename H> friend H AbslHashValue(H _h, const Constant &_const);

protected: 
    bool Compare(const IndexedSymbol &_other) const override
  {
        auto cast =
          dynamic_cast<const Constant &>(_other);
        return this->name_ == cast.name_ && this->indexes == cast.indexes;
    }
};

template <typename H> H AbslHashValue(H _h, const or2l::Constant &_const)
{
    return H::combine(std::move(_h), _const.name_, _const.GetIndexes());
}

enum class VariableType
{
    CONTINUOUS,
    INTEGER,
    BINARY
};

class Variable : public IndexedSymbol
{
  public:
    Variable() : IndexedSymbol("", SymbolType::VARIABLE, {}){};
    Variable(const base_types::RegexString &_name, VariableType _var_type = VariableType::CONTINUOUS,
             std::initializer_list<Index> _indexes = {})
        : IndexedSymbol(_name, SymbolType::VARIABLE, _indexes), variable_type_(_var_type)
    {
        for (const auto &index : _indexes)
        {
            indexes[(index.GetName())] = index;
        }
    };
    virtual ~Variable() = default;

    template <typename H> friend H AbslHashValue(H _h, const Variable &_var);

    VariableType GetVariableType() const
    {
        return variable_type_;
    };

  private:
    bool Compare(const IndexedSymbol &_other) const override
    {
        auto cast = dynamic_cast<const Variable &>(_other);
        return this->name_ == cast.name_ && this->indexes == cast.indexes &&
               this->variable_type_ == cast.variable_type_;
    }

    VariableType variable_type_ = VariableType::CONTINUOUS;
};

template <typename H> H AbslHashValue(H _h, const or2l::Variable &_var)
{
    return H::combine(std::move(_h), _var.name_, _var.GetIndexes(), _var.variable_type_);
}
} // namespace or2l
