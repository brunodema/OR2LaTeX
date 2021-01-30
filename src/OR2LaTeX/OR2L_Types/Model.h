#pragma once
#include "Constraint.h"
#include "Index.h"
#include "RegexString.h"
#include "SolverType.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableSet.h"
#include "gurobi_c++.h"
#include "ortools/linear_solver/linear_solver.h"
#include <map>
#include <string>

using operations_research::MPSolver;

namespace or2l {

template <class T = MPSolver>
class Model {
 public:
  Model(const RegexString& name, std::initializer_list<Index> indexes,
        std::initializer_list<Variable> variables,
        std::initializer_list<Constraint> constraints);
  Model(const RegexString& name) : name_(name) {}
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

  virtual void CreateModel() = 0;
  inline void DestroyModel() { model_.reset(); };
  inline const T* GetModel() { return model_.get(); };

 protected:
  RegexString name_ = "";
  std::unique_ptr<T> model_;
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};

class ModelORTOOLS : public Model<MPSolver> {
 public:
  ModelORTOOLS(const RegexString& name, ORTSolverType type);

  void CreateModel() override {
    model_ = std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverType::GetType(type_)));
  }

 private:
  ORTSolverType type_ = ORTSolverType::CBC;
};

#ifdef GUROBI
class ModelGUROBI : public Model<GRBModel> {
 public:
  ModelGUROBI(const RegexString& name, const GRBEnv& env);

  void CreateModel() override { model_ = std::make_unique<GRBModel>(*env_); }

 private:
  std::unique_ptr<GRBEnv> env_ = nullptr;
};
#endif  // GUROBI

}  // namespace or2l
