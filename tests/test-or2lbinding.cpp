
#include "Model.h"
#include "ModuleTester.h"
#include "ortools/linear_solver/linear_solver.h"

using operations_research::MPConstraint;
using operations_research::MPObjective;
using operations_research::MPSolver;
using operations_research::MPVariable;
using or2l::base_types::ModuleTester;

std::vector<std::function<void()>> ModuleTester::tests_ = {
    []() {
      // model binding
      or2l::Model model("VRP",
                        ORTSolverType::CBC);  // creates only 'or2l' object
      ASSERT_THROW(model.GetObjects(),
                   std::out_of_range);  // throws or 'null' (no object created)
      model.CreateObjects();    // throws (no model type set)
      const auto* a = model.GetObjects();  // throws or 'null' (no object created)
      // (and pointer)
      model.DestroyObjects();  // destroys underlying object (and
      // pointer)
    },
    []() {
      // variable binding
    }};

int main() { return ModuleTester::Run(); }