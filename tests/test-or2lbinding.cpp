
#include "symbol/Constraint.h"
#include "symbol/Index.h"
#include "symbol/MathExpression.h"
#include "model/Model.h"
#include "solver/SolverType.h"
#include "symbol/Variable.h"

#include "gtest/gtest.h"
#include "ortools/linear_solver/linear_solver.h"

#if GUROBI
#include "gurobi_c++.h"
#endif // GUROBI

using or2l::Constraint;
using or2l::Index;
using or2l::MathExpression;
using or2l::MathExpressionOperatorType;
using or2l::Model;
using or2l::SolverType;
using or2l::Variable;
using or2l::VariableType;

TEST(VariableBinding, Test1)
{
    Index i("i", 0, 20);
    Index j("j", 0, 20);
    Variable x("x", VariableType::CONTINUOUS, {i, j});
    Variable c("c", VariableType::CONTINUOUS, {i});

    Model model("test");

    model.AddVariable(x);
    model.AddVariable(c);

    model.DefineSolver(SolverType::ORTOOLS_CBC);
    model.ImplementModel();


}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


/*
the big test!
(http://www.hungarianalgorithm.com/solve.php?c=21-5-1-27--39-55-41-59--90-85-46-52--14-91-53-39&random=1)
solve the assignment problem using both 'ortools' and
'gubori' matrix =  { 21  5   1   27 } { 39  55  41  59 }
    { 90  85  46  52 }
    { 14  91  43  39 }
O.F: min W = c_ij * x_ij
st.
SUM_{i = 1}^{n} x_ij == 1;    FOR(j = 1, n)
SUM_{j = 1}^{n} x_ij == 1;    FOR(i = 1, n)

x_ij as a binary variable

the answer is: 5 41 52 14

expected result:
const int N = 4;
const or2l::vecxd<int> cost_matrix({4,4}, 0);

// set the cost_matrix values...

std::unique_ptr<GRBEnv> env = std::make_unique<GRBEnv>();
std::unique_ptr<Model<MPSolver>> model =
std::make_unique<ModelGUROBI>("model", *env);

model->AddVariable(Variable x_ij("x_ij", BINARY, {i,j}));
model->AddConstraint(Constraint c1("c1", SUM(x_ij, {i, 1, N}) <= 1, FOR(j,1,N)); 
model->AddConstraint(Constraint c2("c2", SUM(x_ij, {j, 1, N}) <= 1, FOR(i,1,N)); 
model->AddOF(ObjectiveFunctionOF("OF", MINIMIZE, c_ij* SUM{x_ij, {i, 1, N}, {j, 1, N}}));
model->FireUp();
model->Solve();

*/