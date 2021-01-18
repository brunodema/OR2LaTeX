#include "Model.h"

namespace or2l {
Model::Model(const RegexString& name, const ORTSolverType solver_type,
             const std::initializer_list<Index> indexes,
             const std::initializer_list<Variable> variables,
             const std::initializer_list<Constraint> constraints)
    : name_(name), solver_type_(solver_type) {
  for (auto&& index : indexes) {
    symbol_map_.insert_or_assign(index.GetName(),
                                 std::make_unique<Index>(index));
  }
  for (auto&& variable : variables) {
    symbol_map_.insert_or_assign(variable.GetName(),
                                 std::make_unique<Variable>(variable));
  }
  for (auto&& constraint : constraints) {
    symbol_map_.insert_or_assign(constraint.GetName(),
                                 std::make_unique<Constraint>(constraint));
  }
}

[[nodiscard]] SymbolComponent* Model::Get(const RegexString& str) const {
  // SymbolType type = symbol_map_.at(str).get()->GetType();
  switch (const SymbolType type = symbol_map_.at(str).get()->GetType()) {
    case SymbolType::INDEX:
      return static_cast<Index*>(symbol_map_.at(str).get());
      break;

    case SymbolType::VARIABLE:
      return static_cast<Variable*>(symbol_map_.at(str).get());
      break;

    case SymbolType::VARIABLE_SET:
      return static_cast<VariableSet*>(symbol_map_.at(str).get());
      break;

    case SymbolType::CONSTRAINT:
      return static_cast<Constraint*>(symbol_map_.at(str).get());
      break;

    default:
      throw Exception();
  }
}

void Model::Remove(const RegexString& str) { symbol_map_.erase(str); }

void Model::AddVariable(const Variable& var) {
  symbol_map_.insert_or_assign(var.GetName(), std::make_unique<Variable>(var));
}

void Model::RemoveVariable(const Variable& var) {
  symbol_map_.erase(var.GetName());
}

void Model::ExtractIndexes(const Variable& var) {
  for (auto&& index : var.GetIndexes()) {
    symbol_map_.insert_or_assign(index.GetName(),
                                 std::make_unique<Index>(index));
  }
}

void Model::AddIndex(const Index& index) {
  symbol_map_.insert_or_assign(index.GetName(), std::make_unique<Index>(index));
}

void Model::RemoveIndex(const Index& index) {
  symbol_map_.erase(index.GetName());
}

void Model::AddVariableSet(const VariableSet& var_set) {
  symbol_map_.insert_or_assign(var_set.GetName(),
                               std::make_unique<VariableSet>(var_set));
}

void Model::RemoveVariableSet(const VariableSet& var_set) {
  symbol_map_.erase(var_set.GetName());
}

void Model::AddConstraint(const Constraint& constraint) {
  symbol_map_.insert_or_assign(constraint.GetName(),
                               std::make_unique<Constraint>(constraint));
}

void Model::RemoveConstraint(const Constraint& constraint) {
  symbol_map_.erase(constraint.GetName());
}
}  // namespace or2l