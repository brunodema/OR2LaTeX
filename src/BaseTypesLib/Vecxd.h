#pragma once
#include "boost/multi_array.hpp"
#include <initializer_list>
#include <iostream>
#include <optional>
#include <vector>

namespace or2l::base_types {

template <typename T>
// bless Hugues from Stack Overflow >>>
// https://stackoverflow.com/questions/37089848/variable-array-dimension-at-runtime-c
// just added some asserts to verify input sizes + personal refactorings
class MultiArray {
 public:
  MultiArray(const std::initializer_list<int>& dims)
      : dims_(dims), data_(CalculateLinearDimension(dims_)) {}
  [[nodiscard]] const std::vector<int>& dims() const { return dims_; }
  const T& operator[](const std::initializer_list<int>& indices) const {
    return data_[index(indices)];
  }
  T& operator[](const std::initializer_list<int>& indices) {
    return data_[index(indices)];
  }

 private:
  std::vector<int> dims_;
  std::vector<T> data_;
  static size_t CalculateLinearDimension(const std::vector<int>& dims) {
    size_t result = 1;
    for (size_t i = 0; i < dims.size(); ++i) result *= size_t(dims[i]);
    return result;
  }
  [[nodiscard]] std::size_t index(const std::vector<int>& indices) const {
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

template <class T, size_t N>
class TestVecxd : public boost::multi_array<T, N> {
 public:
  TestVecxd(std::initializer_list<T>& args) : boost::multi_array<T, N>(args) {}
};

template <class T>
class Vecxd : public std::vector<std::vector<T>> {
 public:
  Vecxd(std::initializer_list<size_t> sizes,
        const T& default_initializer)  // the default initializer never did
                                       // anything here or below... fix it
  {
    this->resize(sizes.size());
    int i = 0;
    for (auto sz : sizes) {
      this->at(i).resize(sz, default_initializer);
      ++i;
    }
  }

  Vecxd(std::initializer_list<size_t> sizes) {
    this->resize(sizes.size());
    int i = 0;
    for (auto sz : sizes) {
      this->at(i).resize(sz);
      ++i;
    }
  }

  Vecxd() = default;

  void FillWith(const T& content) {
    for (auto& vec : *this) {
      std::fill(vec.begin(), vec.end(), content);
    }
  };

  void ReserveContents(std::initializer_list<size_t> sizes) {
    this->resize(sizes.size());  // this one HAS to be a resize, otherwise the
                                 // positions will not be reachable
    int i = 0;
    for (auto const& size : sizes) {
      this->at(i).reserve(size);
      ++i;
    }
  };

  void ResizeContents(std::initializer_list<size_t> sizes,
                      const T& template_object) {
    this->resize(sizes.size());
    int i = 0;
    for (auto const& size : sizes) {
      this->at(i).resize(size, template_object);
      ++i;
    }
  };

 private:
  inline void CheckInitSize(size_t M) const {
    if (M <= 0) {
      throw;
    }
  }
};
}  // namespace or2l::base_types