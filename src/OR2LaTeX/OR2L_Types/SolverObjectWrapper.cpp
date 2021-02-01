#include "SolverObjectWrapper.h"

namespace or2l {
template <class T>
SolverVariableWrapper<T>::SolverVariableWrapper(
    const Variable& var, std::weak_ptr<T> object,
    std::initializer_list<size_t> index_value)
    : object_(object_object) {
  if (indexes.size() != index_value.size()) {
    throw std::invalid_argument(
        "Number of index values provided do no match then number of indexes "
        "declared for the variable");  // change this to or2l::Exception later
                                       // (better string management)
  }
  size_t it = 0;
  for (auto val : index_value) {
    auto ret = index_value_map_.emplace(indexes.at(it), val);
    if (!ret.second) {
      throw std::invalid_argument(
          "An invalid parameter was providaded to the 'SolverVariableWrapper' "
          "constructor");  // change this to or2l::Exception later (better
                           // string management)
    }
    ++it;
  }
}
SolverVariableWrapper<GRBVar>;
SolverVariableWrapper<MPVariable>;
}  // namespace or2l
