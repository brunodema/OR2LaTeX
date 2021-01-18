#pragma once
#include "Constraint.h"
#include "Index.h"
#include "ObjectWrapper.h"
#include "RegexString.h"
#include "SolverType.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableSet.h"
#include "ortools/linear_solver/linear_solver.h"
#include <map>
#include <string>

namespace or2l {
class Model : public ObjectWrapper<operations_research::MPSolver> {
 public:
  Model(const RegexString& name, ORTSolverType solver_type,
        std::initializer_list<Index> indexes,
        std::initializer_list<Variable> variables,
        std::initializer_list<Constraint> constraints);
  Model(const RegexString& name, ORTSolverType solver_type)
      : name_(name), solver_type_(solver_type) {}
  virtual ~Model() = default;

  [[nodiscard]] SymbolComponent* Get(const RegexString& str) const;

  void RemoveSymbol(const RegexString& str);
  void AddVariable(const Variable& var);
  void RemoveVariable(const Variable& var);
  void ExtractIndexes(const Variable& var);
  void AddIndex(const Index& index);
  void RemoveIndex(const Index& index);
  void AddVariableSet(const VariableSet& var_set);
  void RemoveVariableSet(const VariableSet& var_set);
  void AddConstraint(const Constraint& constraint);
  void RemoveConstraint(const Constraint& constraint);

  void CreateObjects() override;
  void DestroyObjects() override;
  const operations_research::MPSolver* GetObjects() override;

 private:
  RegexString name_ = "";
  ORTSolverType solver_type_;
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};
}  // namespace or2l