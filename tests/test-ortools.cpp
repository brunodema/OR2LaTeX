#include "ModuleTester.h"
#include "ortools/constraint_solver/constraint_solver.h"
#include "ortools/linear_solver/linear_solver.h"

using base_types::ModuleTester;
using operations_research::MPConstraint;
using operations_research::MPObjective;
using operations_research::MPSolver;
using operations_research::MPVariable;

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
      // [START solver]
      // Create the linear solver with the GLOP backend.
      MPSolver* solver = MPSolver::CreateSolver("GLOP");
      // [END solver]

      // [START variables]
      const double infinity = operations_research::MPSolver::infinity();
      // Create the variables x and y.
      MPVariable* const x = solver->MakeNumVar(0.0, infinity, "x");
      MPVariable* const y = solver->MakeNumVar(0.0, infinity, "y");

      LOG(INFO) << "Number of variables = " << solver->NumVariables();
      // [END variables]

      // [START constraints]
      // x + 7 * y <= 17.5.
      MPConstraint* const c0 = solver->MakeRowConstraint(-infinity, 17.5, "c0");
      c0->SetCoefficient(x, 1);
      c0->SetCoefficient(y, 7);

      // x <= 3.5.
      MPConstraint* const c1 = solver->MakeRowConstraint(-infinity, 3.5, "c1");
      c1->SetCoefficient(x, 1);
      c1->SetCoefficient(y, 0);

      LOG(INFO) << "Number of constraints = " << solver->NumConstraints();
      // [END constraints]

      // [START objective]
      // Maximize x + 10 * y.
      MPObjective* const objective = solver->MutableObjective();
      objective->SetCoefficient(x, 1);
      objective->SetCoefficient(y, 10);
      objective->SetMaximization();
      // [END objective]

      // [START solve]
      const MPSolver::ResultStatus result_status = solver->Solve();
      // Check that the problem has an optimal solution.
      if (result_status != MPSolver::OPTIMAL) {
        LOG(FATAL) << "The problem does not have an optimal solution!";
      }
      // [END solve]

      // [START print_solution]
      LOG(INFO) << "Solution:" << std::endl;
      LOG(INFO) << "Objective value = " << objective->Value();
      LOG(INFO) << "x = " << x->solution_value();
      LOG(INFO) << "y = " << y->solution_value();
      // [END print_solution]

      // [START advanced]
      LOG(INFO) << "\nAdvanced usage:";
      LOG(INFO) << "Problem solved in " << solver->wall_time()
                << " milliseconds";
      LOG(INFO) << "Problem solved in " << solver->iterations()
                << " iterations";
      // LOG(INFO) << "Problem solved in " << solver->nodes() << "
      // branch-and-bound nodes"; [END advanced]
    },
    []() {
      // Create the mip solver with the SCIP backend.
      MPSolver* solver = MPSolver::CreateSolver("SCIP");

      const double infinity = solver->infinity();
      // x and y are integer non-negative variables.
      MPVariable* const x = solver->MakeIntVar(0.0, infinity, "x");
      MPVariable* const y = solver->MakeIntVar(0.0, infinity, "y");

      LOG(INFO) << "Number of variables = " << solver->NumVariables();

      // x + 7 * y <= 17.5.
      MPConstraint* const c0 = solver->MakeRowConstraint(-infinity, 17.5, "c0");
      c0->SetCoefficient(x, 1);
      c0->SetCoefficient(y, 7);

      // x <= 3.5.
      MPConstraint* const c1 = solver->MakeRowConstraint(-infinity, 3.5, "c1");
      c1->SetCoefficient(x, 1);
      c1->SetCoefficient(y, 0);

      LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

      // Maximize x + 10 * y.
      MPObjective* const objective = solver->MutableObjective();
      objective->SetCoefficient(x, 1);
      objective->SetCoefficient(y, 10);
      objective->SetMaximization();

      const MPSolver::ResultStatus result_status = solver->Solve();
      // Check that the problem has an optimal solution.
      if (result_status != MPSolver::OPTIMAL) {
        LOG(FATAL) << "The problem does not have an optimal solution!";
      }

      LOG(INFO) << "Solution:";
      LOG(INFO) << "Objective value = " << objective->Value();
      LOG(INFO) << "x = " << x->solution_value();
      LOG(INFO) << "y = " << y->solution_value();

      LOG(INFO) << "\nAdvanced usage:";
      LOG(INFO) << "Problem solved in " << solver->wall_time()
                << " milliseconds";
      LOG(INFO) << "Problem solved in " << solver->iterations()
                << " iterations";
      LOG(INFO) << "Problem solved in " << solver->nodes()
                << " branch-and-bound nodes";
    },
    []() {
      // Maximize
      // 𝑧 = 𝑥1 + 𝑥2 + 2*𝑥3 − 2*𝑥4
      // subject to
      // 𝑥1 + 2*𝑥3 ≤ 700
      // 2*𝑥2 − 8*𝑥3 ≤ 0
      // 𝑥2 − 2*𝑥3 + 𝑥4 ≥ 1
      // 𝑥1 + 𝑥2 + 𝑥3 + 𝑥4 = 10
      // 0 ≤ 𝑥1 ≤ 10
      // 0 ≤ 𝑥2 ≤ 10
      // 0 ≤ 𝑥3 ≤ 10
      // 0 ≤ 𝑥4 ≤ 10
      // All variables are integers.
      // The solution (see Example 1 below) is x1 = 3, x2 = 4, x3 = 2, and x4 =
      // 1 which results in z = 9.0. Note that this is quite different from the
      // LP solution of x1 = 9, x2 = 0.8, x3 = 0, and x4 = 0.2 which results in
      // z = 9.4

      // The source is
      // https://ncss-wpengine.netdna-ssl.com/wp-content/themes/ncss/pdf/Procedures/NCSS/Mixed_Integer_Programming.pdf
      // PS: which managed to wrongfully write the problem (check the source
      // link)

      MPSolver* solver = MPSolver::CreateSolver("CBC");
      const double infinity = operations_research::MPSolver::infinity();

      MPVariable* const x1 = solver->MakeIntVar(0, 10, "x1");
      MPVariable* const x2 = solver->MakeIntVar(0, 10, "x2");
      MPVariable* const x3 = solver->MakeIntVar(0, 10, "x3");
      MPVariable* const x4 = solver->MakeIntVar(0, 10, "x4");

      MPObjective* const objective = solver->MutableObjective();
      objective->SetCoefficient(x1, 1);
      objective->SetCoefficient(x2, 1);
      objective->SetCoefficient(x3, 2);
      objective->SetCoefficient(x4, -2);
      objective->SetMaximization();

      MPConstraint* const cstr1 = solver->MakeRowConstraint(0, 700);
      cstr1->SetCoefficient(x1, 1);
      cstr1->SetCoefficient(x3, 2);

      MPConstraint* const cstr2 = solver->MakeRowConstraint(-infinity, 0);
      cstr2->SetCoefficient(x2, 2);
      cstr2->SetCoefficient(x4, -8);

      MPConstraint* const cstr3 = solver->MakeRowConstraint(1, infinity);
      cstr3->SetCoefficient(x2, 1);
      cstr3->SetCoefficient(x3, -2);
      cstr3->SetCoefficient(x4, 1);

      MPConstraint* const cstr4 = solver->MakeRowConstraint(10, 10);
      cstr4->SetCoefficient(x1, 1);
      cstr4->SetCoefficient(x2, 1);
      cstr4->SetCoefficient(x3, 1);
      cstr4->SetCoefficient(x4, 1);

      LOG(INFO) << "Number of variables = " << solver->NumVariables();
      LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

      const MPSolver::ResultStatus result_status = solver->Solve();

      if (result_status != MPSolver::OPTIMAL) {
        LOG(FATAL) << "The problem does not have an optimal solution!";
      }

      LOG(INFO) << "Solution:";
      LOG(INFO) << "Objective value = " << objective->Value();
      LOG(INFO) << "x1 = " << x1->solution_value();
      LOG(INFO) << "x2 = " << x2->solution_value();
      LOG(INFO) << "x3 = " << x3->solution_value();
      LOG(INFO) << "x4 = " << x4->solution_value();

      LOG(INFO) << "\nAdvanced usage:";
      LOG(INFO) << "Problem solved in " << solver->wall_time()
                << " milliseconds";
      LOG(INFO) << "Problem solved in " << solver->iterations()
                << " iterations";
      LOG(INFO) << "Problem solved in " << solver->nodes()
                << " branch-and-bound nodes";
    }};

int main() { return ModuleTester::Run(); }