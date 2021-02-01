#pragma once
#include "Variable.h"
#include "ortools/linear_solver/linear_solver.h"
#include <unordered_map>
#ifdef GUROBI
#include "gurobi_c++.h"
#endif  // GUROBI

namespace or2l {
using operations_research::MPVariable;
template <class T>
class SolverVariableWrapper {
 public:
  SolverVariableWrapper(const Variable& var, std::weak_ptr<T> object,
                        std::initializer_list<size_t> index_value);
  virtual ~SolverVariableWrapper() = default;

 protected:
  std::weak_ptr<T> object_= nullptr;
  std::unordered_map<Index, size_t> index_value_map_ = {};
};
}  // namespace or2l