
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
      std::unique_ptr<Model<GRBModel>> model_gurobi =
          std::make_unique<ModelGUROBI>("gurobi", *env);
      model_gurobi->CreateModel();
      const auto* b = model_gurobi->GetModel();
      model_gurobi->DestroyModel();
    },
    []() {
      /*
      the big test!
      (http://www.hungarianalgorithm.com/solve.php?c=21-5-1-27--39-55-41-59--90-85-46-52--14-91-53-39&random=1)
      solve the assignment problem using both 'ortools' and 'gubori'
      matrix =  { 21  5   1   27 }
                { 39  55  41  59 }
                { 90  85  46  52 }
                { 14  91  43  39 }
      O.F: min W = c_ij * x_ij
      st.
      SUM_{i = 1}^{n} x_ij == 1;    FOR(j = 1, n)
      SUM_{j = 1}^{n} x_ij == 1;    FOR(i = 1, n)

      x_ij as a binary variable

      the answer is: 5
                     41
                     52
                     14
      */

      /*
      expected result:




       */
    }};

int main() { return ModuleTester::Run(); }