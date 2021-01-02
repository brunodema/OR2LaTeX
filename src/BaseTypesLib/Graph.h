#pragma once
#include "Coordinates.h"
#include <functional>
#include <vector>

namespace or2l::base_types {
template <class T>
class IGraph {
 public:
  virtual void CalculateDistanceMatrix() = 0;
  virtual T GetDistance(const Coordinates<T>& a,
                        const Coordinates<T>& b) const {
    return distanceFunction(a, b);
  };

  virtual ~IGraph() = default;

 protected:
  std::vector<Coordinates<T>> coordinates_;
  std::function<T(Coordinates<T>, Coordinates<T>)> distance_function_;
};

template <class T>
class Graph : public IGraph<T> {
 public:
  explicit Graph(std::vector<Coordinates<T>> coords,
                 std::function<T(Coordinates<T>, Coordinates<T>)> dfunc = {}) {
    this->coordinates = coords;
    this->distanceFunction = dfunc;
  }
};

}  // namespace or2l::base_types