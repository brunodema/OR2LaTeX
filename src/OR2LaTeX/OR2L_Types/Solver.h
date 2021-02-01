#pragma once
#include "SolverType.h"
#include "Variable.h"
#include "VariableType.h"
#include "SolverObjectWrapper.h"
#include "ortools/linear_solver/linear_solver.h"
#ifdef GUROBI
#include "gurobi_c++.h"
#endif

namespace or2l {
using operations_research::MPSolver;
class Solver {
 public:
  Solver() = default;
  ~Solver() = default;

  virtual void ImplementModel() = 0;
  virtual void FreeModel() = 0;

  // virtual void AddVariable(const Variable& var) = 0;
  // virtual void RemoveVariable(const Variable& var) = 0;

 protected:
  // virtual void AddConstraint(const Constraint& constraint) = 0;
  // virtual void RemoveConstraint(const Constraint& constraint) = 0;
};

class OrtoolsSolver : public Solver {
 public:
  explicit OrtoolsSolver(const SolverType type) : type_(type) {
    assert((int)type <= SOLVERTYPE_ORTOOLS_MAX);
  }
  ~OrtoolsSolver() = default;

  void ImplementModel() override {
    model_ = std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverTypeDictionary::GetType(type_)));
  }
  void FreeModel() override { model_.reset(); }

  // void AddVariable(const Variable& var) override {}
  // void RemoveVariable(const Variable& var) override {}

 private:
  SolverType type_;
  std::unique_ptr<MPSolver> model_ = nullptr;
};  // namespace or2l

#ifdef GUROBI
class GurobiSolver : public Solver {
 public:
  explicit GurobiSolver(const GRBEnv& env)
      : env_(std::make_unique<GRBEnv>(env)) {}
  ~GurobiSolver() = default;

  void ImplementModel() override { model_ = std::make_unique<GRBModel>(*env_); }
  void FreeModel() override { model_.reset(); }

 private:
  std::unique_ptr<GRBEnv> env_ = nullptr;
  std::unique_ptr<GRBModel> model_ = nullptr;
};
#endif  // GUROBI
}  // namespace or2l