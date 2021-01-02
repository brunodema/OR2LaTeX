#pragma once
#include "Constraint.h"
#include "Index.h"
#include "RegexString.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableSet.h"
#include <map>
#include <string>

namespace or2l {
class Model {
 public:
  Model(const RegexString& name, const std::initializer_list<Index> indexes,
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

  explicit Model(const RegexString& name) : name_(name) {}
  virtual ~Model() = default;

  [[nodiscard]] SymbolComponent* Get(const RegexString& str) const {
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

  void Remove(const RegexString& str) { symbol_map_.erase(str); }

  void AddVariable(const Variable& var) {
    symbol_map_.insert_or_assign(var.GetName(),
                                 std::make_unique<Variable>(var));
  }

  void RemoveVariable(const Variable& var) { symbol_map_.erase(var.GetName()); }

  void ExtractIndexes(const Variable& var) {
    for (auto&& index : var.GetIndexes()) {
      symbol_map_.insert_or_assign(index.GetName(),
                                   std::make_unique<Index>(index));
    }
  }

  void AddIndex(const Index& index) {
    symbol_map_.insert_or_assign(index.GetName(),
                                 std::make_unique<Index>(index));
  }

  void RemoveIndex(const Index& index) { symbol_map_.erase(index.GetName()); }

  void AddVariableSet(const VariableSet& var_set) {
    symbol_map_.insert_or_assign(var_set.GetName(),
                                 std::make_unique<VariableSet>(var_set));
  }

  void RemoveVariableSet(const VariableSet& var_set) {
    symbol_map_.erase(var_set.GetName());
  }

  void AddConstraint(const Constraint& constraint) {
    symbol_map_.insert_or_assign(constraint.GetName(),
                                 std::make_unique<Constraint>(constraint));
  }

  void RemoveConstraint(const Constraint& constraint) {
    symbol_map_.erase(constraint.GetName());
  }

 private:
  RegexString name_ = "";
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};
}  // namespace or2l