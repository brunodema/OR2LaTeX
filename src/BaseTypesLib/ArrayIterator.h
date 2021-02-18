#pragma once
#include "Bounds.h"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace or2l::base_types {
class ArrayIterator {
 public:
  explicit ArrayIterator(std::vector<Bounds> bounds)
      : bounds_(std::move(bounds)) {
    for (const auto& bound : bounds_) {
      max_iter_ *= (bound.ub - bound.lb);
      current_.push_back(bound.lb);
    }
  }
  explicit ArrayIterator(const std::vector<std::size_t>& sizes) {
    for (const auto& size : sizes) {
      max_iter_ *= size;
      bounds_.emplace_back(0, size);
      current_.emplace_back(0);
    }
  }

  static void Print(std::vector<std::size_t>& combination,
                    const size_t curr_iter) {
#ifdef _DEBUG_PRINT

    std::cout << "{";
    for (auto&& i = 0; i < combination.size(); ++i) {
      std::cout << combination[i];
      if (i < combination.size() - 1) std::cout << ",";
    }
    std::cout << "}, current iteration: << " << curr_iter << "\n";

#endif
  }

  [[nodiscard]] bool HasNext() const { return counter_ <= max_iter_; }

  std::vector<std::size_t> Next() {
    if (counter_ == 1) {
      Print(current_, counter_);
      ++counter_;
      return current_;
    }
    if (current_.back() + 1 == bounds_.back().ub) {
      current_ = IncreaseToTheLeft();
      Print(current_, counter_);
      ++counter_;
      return current_;
    }
    ++current_.back();
    Print(current_, counter_);
    ++counter_;
    return current_;
  }

  std::vector<std::vector<std::size_t>> Iterate() {
    std::vector<std::vector<std::size_t>> ret;
    while (HasNext()) {
      ret.push_back(Next());
    }
    return ret;
  }

  [[nodiscard]] std::size_t GetCounter() const { return counter_; }

  [[nodiscard]] std::string GetCurrentCombinationString() const {
    std::string ret;
    for (const auto& i : current_) {
      ret += &"_"[i];
    }
    return ret;
  }

 private:
  std::vector<Bounds> bounds_ = {};
  std::size_t max_iter_ = 1;
  std::size_t counter_ = 1;
  std::vector<std::size_t> current_ = {};

  std::vector<std::size_t> IncreaseToTheLeft() {
    if (current_.size() == 1) {
      return current_;
    }
    for (auto&& i = bounds_.size() - 2; i < bounds_.size(); --i) {
      if (current_[i] + 1 < bounds_[i].ub) {
        ++current_[i];
        for (auto&& ii = i + 1; ii < bounds_.size(); ++ii) {
          current_[ii] = 0;
        }
        return current_;
      }
    }
    return current_;
  }
};
}  // namespace or2l::base_types