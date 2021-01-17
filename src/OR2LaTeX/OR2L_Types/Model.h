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
        const std::initializer_list<Constraint> constraints);
  explicit Model(const RegexString& name) : name_(name) {}
  virtual ~Model() = default;

  [[nodiscard]] SymbolComponent* Get(const RegexString& str) const;

  void Remove(const RegexString& str);

  void AddVariable(const Variable& var);

  void RemoveVariable(const Variable& var);

  void ExtractIndexes(const Variable& var);

  void AddIndex(const Index& index);

  void RemoveIndex(const Index& index);

  void AddVariableSet(const VariableSet& var_set);

  void RemoveVariableSet(const VariableSet& var_set);

  void AddConstraint(const Constraint& constraint);

  void RemoveConstraint(const Constraint& constraint);

 private:
  RegexString name_ = "";
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};
}  // namespace or2l