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
// just added some asserts to verify input sizes
class MultiArray {
 public:
  MultiArray(const std::initializer_list<int>& dims)
      : m_dims(dims), m_data(product(m_dims)) {}
  const std::vector<int>& dims() const { return m_dims; }
  const T& operator[](const std::initializer_list<int>& indices) const {
    return m_data[index(indices)];
  }
  T& operator[](const std::initializer_list<int>& indices) {
    assert(indices.size() == m_dims.size());
    return m_data[index(indices)];
  }

 private:
  std::vector<int> m_dims;
  std::vector<T> m_data;
  static size_t product(const std::vector<int>& dims) {
    size_t result = 1;
    for (size_t i = 0; i < dims.size(); ++i) result *= size_t(dims[i]);
    return result;
  }
  size_t index(const std::vector<int>& indices) const {
    size_t v = 0;
    for (size_t i = 0; i < m_dims.size(); ++i) {
      assert(indices.size() == m_dims.size());
      assert(indices[i] >= 0 && indices[i] < m_dims[i]);
      if (i) v *= size_t(m_dims[i]);
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