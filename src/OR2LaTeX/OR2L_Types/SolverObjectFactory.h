#pragma once
#include "SolverType.h"
#include "ortools/linear_solver/linear_solver.h"

#ifdef GUROBI
#pragma message "Compiling with 'GUROBI'"
#include "gurobi_c++.h"
#endif  // GUROBI

using operations_research::MPSolver;

namespace or2l {
class SolverObjectFactory {
 public:
  SolverObjectFactory() = delete;

  static std::unique_ptr<MPSolver> CreateModel(ORTSolverType type) {
    return std::unique_ptr<MPSolver>(
        MPSolver::CreateSolver(SolverType::GetType(type)));
  }

#ifdef GUROBI
  static std::unique_ptr<GRBModel> CreateModel(const GRBEnv& env) {
    return std::make_unique<GRBModel>(GRBModel(env));
  }
#endif  // GUROBI
};
}  // namespace or2l
