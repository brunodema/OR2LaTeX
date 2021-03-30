#include "Model.h"

namespace or2l
{

Model::Model(const base_types::RegexString &_name, const std::initializer_list<Index> _indexes,
             const std::initializer_list<Variable> _variables, const std::initializer_list<Constraint> _constraints)
    : name_(_name)
{
    for (auto &&index : _indexes)
    {
        symbol_map_.insert_or_assign(index.GetName(), std::make_unique<Index>(index));
    }
    for (auto &&variable : _variables)
    {
        symbol_map_.insert_or_assign(variable.GetName(), std::make_unique<Variable>(variable));
    }
    for (auto &&constraint : _constraints)
    {
        symbol_map_.insert_or_assign(constraint.GetName(), std::make_unique<Constraint>(constraint));
    }
}

[[nodiscard]] Symbol *Model::Get(const base_types::RegexString &_str) const
{
    // SymbolType type = symbol_map_.at(str).get()->GetType();
    switch (const SymbolType type = symbol_map_.at(_str).get()->GetType())
    {
    case SymbolType::INDEX:
        return static_cast<Index *>(symbol_map_.at(_str).get());
        break;

    case SymbolType::VARIABLE:
        return static_cast<Variable *>(symbol_map_.at(_str).get());
        break;

    case SymbolType::CONSTRAINT:
        return static_cast<Constraint *>(symbol_map_.at(_str).get());
        break;

    default:
        throw Exception();
    }
}

void Model::RemoveSymbol(const base_types::RegexString &_str)
{
    symbol_map_.erase(_str);
}

void Model::AddVariable(const Variable &_var)
{
    symbol_map_.insert_or_assign(_var.GetName(), std::make_unique<Variable>(_var));
}

void Model::RemoveVariable(const Variable &_var)
{
    symbol_map_.erase(_var.GetName());
}

void Model::MapIndexesFromVariable(const Variable &_var)
{
    for (auto &&index : _var.GetIndexes())
    {
        symbol_map_.insert_or_assign(index.GetName(), std::make_unique<Index>(index));
    }
}

void Model::AddIndex(const Index &_index)
{
    symbol_map_.insert_or_assign(_index.GetName(), std::make_unique<Index>(_index));
}

void Model::RemoveIndex(const Index &_index)
{
    symbol_map_.erase(_index.GetName());
}

void Model::AddConstraint(const Constraint &_constraint)
{
    symbol_map_.insert_or_assign(_constraint.GetName(), std::make_unique<Constraint>(_constraint));
}

void Model::RemoveConstraint(const Constraint &_constraint)
{
    symbol_map_.erase(_constraint.GetName());
}
} // namespace or2l