#pragma once
#include "Variable.h"
#include <unordered_map>

namespace or2l {
class SolverVariableWrapper {
 public:
  SolverVariableWrapper(const Variable& var, std::initializer_list<size_t> index_value);
  ~SolverVariableWrapper() = default;

 protected:
  std::unordered_map<Index, size_t> index_value_map_ = {};
};
}  // namespace or2l