#pragma once
#include "SolverObjectWrapper.h"
#include "SolverType.h"
#include "Variable.h"
#include "VariableType.h"
#include "ortools/linear_solver/linear_solver.h"
#ifdef GUROBI
#include "gurobi_c++.h"
#endif

namespace or2l {
using operations_research::MPSolver;
class Solver {
 public:
  Solver() = default;
  virtual ~Solver() = default;

  virtual void ImplementModel() = 0;
  virtual void FreeModel() = 0;

  virtual void AddVariableSet(const Variable& var) = 0;
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
  virtual ~OrtoolsSolver() = default;

  void ImplementModel() override {
    model_ = std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverTypeDictionary::GetType(
            type_)));  // in order to implement the model, the solver needs to
                       // access information about the model ('Variable' for
                       // instance)
  }
  void FreeModel() override { model_.reset(); }

  void AddVariableSet(const Variable& var) override {
    auto indexes = var.GetIndexes();
    auto index_sizes =
        var.GetIndexSizes();  // should reserve first, to avoid a bunch of
                              // resizes mid-through push-backs
    for (const auto& ind : indexes) {
      for (size_t i = 0; i < ind.GetSize(); i++) {
        std::weak_ptr<MPVariable> var_ptr;
        switch (var.GetVariableType()) {
          case VariableType::CONTINUOUS:
            var_ptr = std::shared_ptr<MPVariable>(model_->MakeNumVar(
                0.00, 100000000, var.GetName() + std::to_string(i)));
            break;
          case VariableType::BINARY:
            var_ptr = std::shared_ptr<MPVariable>(
                model_->MakeBoolVar(var.GetName() + std::to_string(i)));
            break;
          case VariableType::INTEGER:
            var_ptr = std::shared_ptr<MPVariable>(model_->MakeIntVar(
                0.00, 100000000, var.GetName() + std::to_string(i)));
            break;
          default:
            throw std::invalid_argument(
                "An invalid variable type was assigned (not CONTINUOUS, "
                "BINARY, or INTEGER)");  // change this to or2l::Exception later
                                         // (better string management)
            break;
            SolverVariableWrapper<MPVariable> a(var, var_ptr, {i});
            variable_vec_.push_back(a);
        }
      }
    }
  }
  // void RemoveVariable(const Variable& var) override {}

 private:
  SolverType type_;
  std::unique_ptr<MPSolver> model_ = nullptr;
  std::vector<SolverVariableWrapper<MPVariable>> variable_vec_ = {};
};  // namespace or2l

#ifdef GUROBI
class GurobiSolver : public Solver {
 public:
  explicit GurobiSolver(const GRBEnv& env)
      : env_(std::make_unique<GRBEnv>(env)) {}
  virtual ~GurobiSolver() = default;

  void ImplementModel() override { model_ = std::make_unique<GRBModel>(*env_); }
  void FreeModel() override { model_.reset(); }

  void AddVariableSet(const Variable& var) override {
  }  // wrote this only so another test could pass

 private:
  std::unique_ptr<GRBEnv> env_ = nullptr;
  std::unique_ptr<GRBModel> model_ = nullptr;
};
#endif  // GUROBI
}  // namespace or2l