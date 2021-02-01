#include "SolverObjectWrapper.h"

namespace or2l {
SolverVariableWrapper::SolverVariableWrapper(
    const Variable& var, std::initializer_list<size_t> index_value) {
  auto indexes = var.GetIndexes();
  if (indexes.size() != index_value.size()) {
    throw std::invalid_argument(
        "Number of index values provided do no match then number of indexes "
        "declared for the variable");
  }
  size_t it = 0;
  for (auto val : index_value) {
    auto ret = index_value_map_.emplace(indexes.at(it), val);
    if (!ret.second) {
      throw std::invalid_argument(
          "An invalid parameter was providaded to the 'SolverVariableWrapper' "
          "constructor");
    }
    ++it;
  }
}
}  // namespace or2l
