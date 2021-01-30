#pragma once
#include "Constraint.h"
#include "Index.h"
#include "RegexString.h"
#include "SolverType.h"
#include "SymbolComponent.h"
#include "Variable.h"
#include "VariableSet.h"
#include "ortools/linear_solver/linear_solver.h"
#include <map>
#include <string>

#ifdef GUROBI
#include "gurobi_c++.h"
#endif  // GUROBI

using operations_research::MPSolver;

namespace or2l {
class Solver {
 public:
  Solver() = default;

  virtual void ImplementModel() = 0;
  virtual void FreeModel() = 0;

 protected:
  // virtual void AddVariable(const Variable& var) = 0;
  // virtual void RemoveVariable(const Variable& var) = 0;
  // virtual void AddConstraint(const Constraint& constraint) = 0;
  // virtual void RemoveConstraint(const Constraint& constraint) = 0;
};

class OrtoolsSolver : public Solver {
 public:
  explicit OrtoolsSolver(const SolverType type) : type_(type) {
    assert(type <= SOLVERTYPE_ORTOOLS_MAX);
  }

  void ImplementModel() override {
    model_ = std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverTypeDictionary::GetType(type_)));
  }
  void FreeModel() override { model_.reset(); }

 private:
  SolverType type_;
  std::unique_ptr<MPSolver> model_ = nullptr;
};  // namespace or2l

#ifdef GUROBI
class GurobiSolver : public Solver {
 public:
  explicit GurobiSolver(const GRBEnv& env)
      : env_(std::make_unique<GRBEnv>(env)) {}

  void ImplementModel() override { model_ = std::make_unique<GRBModel>(*env_); }
  void FreeModel() override { model_.reset(); }

 private:
  std::unique_ptr<GRBEnv> env_ = nullptr;
  std::unique_ptr<GRBModel> model_ = nullptr;
};
#endif  // GUROBI

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

  inline void DefineSolver(const SolverType type) {
    solver_ = std::make_unique<OrtoolsSolver>(type);
  }
#ifdef GUROBI
  inline void DefineSolver(const GRBEnv& env) {
    solver_ = std::make_unique<GurobiSolver>(env);
  }
#endif  // GUROBI
  inline void ImplementModel() {
    if (solver_ == nullptr)
      throw or2l::Exception(ExceptionType::ERR_MODEL_NULLPTRSOLVER);
    solver_->ImplementModel();
  }
  inline void FreeModel() { solver_.reset(); };
  inline const Solver* GetModel() { return solver_.get(); };

 protected:
  RegexString name_ = "";
  std::unique_ptr<Solver> solver_;
  std::map<RegexString, std::unique_ptr<SymbolComponent>> symbol_map_ = {};
};
}  // namespace or2l