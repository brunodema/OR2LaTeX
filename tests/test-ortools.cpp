#include "ModuleTester.h"
#include "ortools/linear_solver/linear_solver.h"

using or2l::base_types::ModuleTester;

std::vector<std::function<void()>> ModuleTester::tests_ = {[]() {
  int a = 1;
  operations_research::MPSolver solver(
      "integer_programming_example",
      operations_research::MPSolver::SCIP_MIXED_INTEGER_PROGRAMMING);
}};

int main() { return ModuleTester::Run(); }