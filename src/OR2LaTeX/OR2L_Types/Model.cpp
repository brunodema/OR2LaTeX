#include "Model.h"
#include "ortools/linear_solver/linear_solver.h"

using operations_research::MPSolver;

namespace or2l {
template <class T>
Model<T>::Model(const RegexString& name,
                const std::initializer_list<Index> indexes,
                const std::initializer_list<Variable> variables,
                const std::initializer_list<Constraint> constraints)
    : name_(name) {
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
template <class T>
[[nodiscard]] SymbolComponent* Model<T>::Get(const RegexString& str) const {
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
template <class T>
void Model<T>::RemoveSymbol(const RegexString& str) {
  symbol_map_.erase(str);
}
template <class T>
void Model<T>::AddVariable(const Variable& var) {
  symbol_map_.insert_or_assign(var.GetName(), std::make_unique<Variable>(var));
}
template <class T>
void Model<T>::RemoveVariable(const Variable& var) {
  symbol_map_.erase(var.GetName());
}
template <class T>
void Model<T>::ExtractIndexes(const Variable& var) {
  for (auto&& index : var.GetIndexes()) {
    symbol_map_.insert_or_assign(index.GetName(),
                                 std::make_unique<Index>(index));
  }
}
template <class T>
void Model<T>::AddIndex(const Index& index) {
  symbol_map_.insert_or_assign(index.GetName(), std::make_unique<Index>(index));
}
template <class T>
void Model<T>::RemoveIndex(const Index& index) {
  symbol_map_.erase(index.GetName());
}
template <class T>
void Model<T>::AddVariableSet(const VariableSet& var_set) {
  symbol_map_.insert_or_assign(var_set.GetName(),
                               std::make_unique<VariableSet>(var_set));
}
template <class T>
void Model<T>::RemoveVariableSet(const VariableSet& var_set) {
  symbol_map_.erase(var_set.GetName());
}
template <class T>
void Model<T>::AddConstraint(const Constraint& constraint) {
  symbol_map_.insert_or_assign(constraint.GetName(),
                               std::make_unique<Constraint>(constraint));
}
template <class T>
void Model<T>::RemoveConstraint(const Constraint& constraint) {
  symbol_map_.erase(constraint.GetName());
}


ModelORTOOLS::ModelORTOOLS(const RegexString& name, ORTSolverType type)
    : Model(name), type_(type) {}

}  // namespace or2l
