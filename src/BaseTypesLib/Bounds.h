#pragma once
#include <cstdlib>
#include <stdexcept>

namespace or2l::base_types {
struct Bounds {
  Bounds(std::size_t lower_bound, std::size_t upper_bound)
      : lb(lower_bound), ub(upper_bound) {
    if (lb >= ub) {
      throw std::invalid_argument(
          "The lower bound can not be bigger that then upper bound.");
    }
  }

  std::size_t lb;
  std::size_t ub;
};
}  // namespace or2l::base_types