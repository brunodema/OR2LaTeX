#pragma once
#include "boost/multi_array.hpp"
#include <initializer_list>
#include <iostream>
#include <optional>
#include <vector>

namespace or2l::base_types {

// bless Hugues from Stack Overflow >>>
// https://stackoverflow.com/questions/37089848/variable-array-dimension-at-runtime-c
// just added some asserts to verify input sizes + personal refactorings
template <typename T>
class MultiArray {
 public:
  MultiArray() = default;
  MultiArray(const std::initializer_list<std::size_t>& dims)
      : dims_(dims), data_(CalculateLinearDimension(dims_)) {}

  void ResizeContents(const std::vector<std::size_t>& dims) {
    dims_ = dims;
    data_.resize(CalculateLinearDimension(dims));
  }
  void FillWith(const T& default_value) {
    std::fill(data_.begin(), data_.end(), default_value);
  }

  [[nodiscard]] const std::vector<std::size_t>& dims() const { return dims_; }
  const T& operator[](const std::initializer_list<std::size_t>& indices) const {
    return data_[index(indices)];
  }
  T& operator[](const std::initializer_list<std::size_t>& indices) {
    return data_[index(indices)];
  }

 private:
  std::vector<std::size_t> dims_;
  std::vector<T> data_;
  static std::size_t CalculateLinearDimension(
      const std::vector<std::size_t>& dims) {
    size_t result = 1;
    for (size_t i = 0; i < dims.size(); ++i) result *= size_t(dims[i]);
    return result;
  }
  [[nodiscard]] std::size_t index(
      const std::vector<std::size_t>& indices) const {
    assert(indices.size() == dims_.size());
    size_t v = 0;
    for (size_t i = 0; i < dims_.size(); ++i) {
      assert(indices[i] >= 0 && indices[i] < dims_[i]);
      if (i) v *= size_t(dims_[i]);
      v += size_t(indices[i]);
    }
    return v;
  }
};
}  // namespace or2l::base_types