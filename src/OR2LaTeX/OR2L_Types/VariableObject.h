#pragma once
#include "Variable.h"
#include <unordered_map>

namespace or2l {
class VariableObject  // redo the association with indexes
{
 public:
  explicit VariableObject(const Variable& variable)
      : template_variable_(variable), index_values_() {}

  VariableObject() = default;

  virtual ~VariableObject() = default;

 private:
  Variable template_variable_ = {};
  std::unordered_map<Index, size_t> index_values_ = {};
};
}  // namespace or2l
