#pragma once
#include "VARIABLE.h"
#include <unordered_map>

namespace or2l {
class VARIABLE_OBJECT  // redo the association with indexes
{
 public:
  explicit VARIABLE_OBJECT(const VARIABLE& variable)
      : template_variable_(variable), index_values_() {}

  VARIABLE_OBJECT() = default;

  virtual ~VARIABLE_OBJECT() = default;

 private:
  VARIABLE template_variable_ = {};
  std::unordered_map<INDEX, size_t> index_values_ = {};
};
}  // namespace or2l
