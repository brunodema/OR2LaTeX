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
      or2l::Model model("VRP");    // creates only 'or2l' object
      model->CreateObjects();      // throws (no model type set)
      created model->GetObject();  // throws or 'null' (no object created)
      created model->SetSolver(
          SolverLibrary::CBC);  // creates underlying object (and pointer)
      model->GetObject();       // gets underlying object (and pointer)
      model->DestroyObjects();  // destroys underlying object (and pointer)
    },
    []() {
      // variable binding
    }};