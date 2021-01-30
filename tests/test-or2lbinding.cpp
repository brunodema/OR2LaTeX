
#include "Model.h"
#include "ModuleTester.h"
#include "ortools/linear_solver/linear_solver.h"

#if GUROBI
#include "gurobi_c++.h"
#endif  // GUROBI

using operations_research::MPConstraint;
using operations_research::MPObjective;
using operations_research::MPSolver;
using operations_research::MPVariable;
using or2l::base_types::ModuleTester;

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
      // model binding
      std::unique_ptr<Model<MPSolver>> model_ortools =
          std::make_unique<ModelORTOOLS>("ortools", ORTSolverType::CBC);
      model_ortools->CreateModel();
      const auto* a = model_ortools->GetModel();
      model_ortools->DestroyModel();

      std::unique_ptr<GRBEnv> env = std::make_unique<GRBEnv>();
      std::unique_ptr<Model<GRBModel>> model_gurobi = std::make_unique<ModelGUROBI>("gurobi", *env);
      model_gurobi->CreateModel();
      const auto* b = model_gurobi->GetModel();
      model_gurobi->DestroyModel();
    },
    []() {
      // variable binding
    }};

int main() { return ModuleTester::Run(); }