
#include "Index.h"
#include "Model.h"
#include "ModuleTester.h"
#include "SolverType.h"
#include "Variable.h"
#include "VariableType.h"
#include "ortools/linear_solver/linear_solver.h"

#if GUROBI
#include "gurobi_c++.h"
#endif  // GUROBI

using base_types::ModuleTester;
using or2l::Index;
using or2l::Model;
using or2l::SolverType;
using or2l::Variable;
using or2l::VariableType;

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
      // model binding
      std::unique_ptr<Model> model_ortools = std::make_unique<Model>("ortools");
      model_ortools->DefineSolver(SolverType::ORTOOLS_CBC);
      model_ortools->ImplementModel();
      const auto* a = model_ortools->GetModel();
      model_ortools->FreeModel();

#ifdef GUROBI
      std::unique_ptr<GRBEnv> env = std::make_unique<GRBEnv>();
      std::unique_ptr<Model> model_gurobi = std::make_unique<Model>("gurobi");
      model_gurobi->DefineSolver(*env);
      model_gurobi->ImplementModel();
      const auto* b = model_gurobi->GetModel();
      model_gurobi->FreeModel();
#endif  // GUROBI
    },
    []() {
      // testing the 'AddVariableSet' function
      Model model("ValidName");
      Index i("i", 0, 20);
      Index j("i", 0, 20);
      Variable x("x", or2l::VariableType::BINARY, {i, j});
      model.AddVariable(x);
      model.DefineSolver(SolverType::ORTOOLS_CBC);
      model.ImplementModel();
    },
    []() {
      Model model("LOL");
      Index i("i", 0, 10);
      Index j("j", 0, 20);
      Variable x_ij("xij", VariableType::CONTINUOUS, {i, j});

      model.AddVariable(x_ij);
      model.DefineSolver(SolverType::ORTOOLS_CBC);
      model.ImplementModel();

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
      const int N = 4;
      const or2l::vecxd<int> cost_matrix({4,4}, 0);

      // set the cost_matrix values...

      std::unique_ptr<GRBEnv> env = std::make_unique<GRBEnv>();
      std::unique_ptr<Model<MPSolver>> model =
      std::make_unique<ModelGUROBI>("model", *env);


      model->AddVariable(Variable x_ij("x_ij", BINARY, {i,j}));
      model->AddConstraint(Constraint c1("c1", SUM(x_ij, {i, 1, N}) <= 1,
      FOR(j,1,N)); model->AddConstraint(Constraint c2("c2", SUM(x_ij, {j, 1, N})
      <= 1, FOR(i,1,N)); model->AddOF(ObjectiveFunction OF("OF", MINIMIZE, c_ij
      * SUM{x_ij, {i, 1, N}, {j, 1, N}})) model->FireUp(); model->Solve();


       */
    }};

int main() { return ModuleTester::Run(); }