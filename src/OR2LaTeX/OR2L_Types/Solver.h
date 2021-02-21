#pragma once
#include "ArrayIterator.h"
#include "SolverType.h"
#include "Variable.h"
#include "VariableType.h"
#include "ortools/linear_solver/linear_solver.h"
#include <map>
#include <utility>
#ifdef GUROBI
#include "gurobi_c++.h"
#endif

template <class T1, class T2>
struct HashPair {
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);
    // XOR is pottentially dangerous here
    return hash1 ^ hash2;
  }
};

using VariableIndexPair = std::pair<or2l::Variable, std::vector<size_t>>;
struct Comp {
  bool operator()(const VariableIndexPair& l,
                  const VariableIndexPair& r) const {
    if (l.first == r.first) {
      if (l.second == r.second) {
        return true;
      }
    }
    return false;
  }
};

namespace or2l {
using base_types::ArrayIterator;
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
  ~OrtoolsSolver() override = default;

  void ImplementModel() override {
    model_ = std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverTypeDictionary::GetType(
            type_)));  // in order to implement the model, the solver needs to
                       // access information about the model ('Variable' for
                       // instance)
  }
  void FreeModel() override { model_.reset(); }

  void AddVariableSet(const Variable& var) override {
    const auto indexes = var.GetIndexSizes();
    auto it = ArrayIterator(indexes);

    while (it.HasNext()) {
      auto current_combination = it.Next();
      std::weak_ptr<operations_research::MPVariable> var_ptr;
      switch (var.GetVariableType()) {
        case VariableType::CONTINUOUS:
          var_ptr = std::shared_ptr<operations_research::MPVariable>(
              model_->MakeNumVar(
                  0.00, 100000000,
                  var.GetName() + it.GetCurrentCombinationString()));
          break;
        case VariableType::BINARY:
          var_ptr = std::shared_ptr<operations_research::MPVariable>(
              model_->MakeBoolVar(var.GetName() +
                                  it.GetCurrentCombinationString()));
          break;
        case VariableType::INTEGER:
          var_ptr = std::shared_ptr<operations_research::MPVariable>(
              model_->MakeIntVar(
                  0.00, 100000000,
                  var.GetName() + it.GetCurrentCombinationString()));
          break;
        default:
          throw std::invalid_argument(
              "An invalid variable type was assigned (not CONTINUOUS, "
              "BINARY, or INTEGER)");  // change this to or2l::Exception later
                                       // (better string management)
          break;
      }
    }
  }
  // void RemoveVariable(const Variable& var) override {}

 private:
  SolverType type_;
  std::unique_ptr<MPSolver> model_ = nullptr;
  std::map<VariableIndexPair,
           std::vector<std::weak_ptr<operations_research::MPVariable>>,
           HashPair<Variable, std::vector<std::size_t>>>
      variable_vec_;
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
