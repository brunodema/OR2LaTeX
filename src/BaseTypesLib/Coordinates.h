#pragma once
#include <iostream>
#include <utility>

namespace or2l::base_types {
template <class T = double>
class Coordinates {
 public:
  std::string Id = "";
  T x = {};
  T y = {};

  Coordinates(std::string pId, const T px, const T py)
      : Id(std::move(pId)), x(px), y(py) {}

  bool operator==(const Coordinates<T>& B)
      const  // the comparisson will target the coordinates themselves, not ids
  {
    return this->x == B.x && this->y == B.y;
  };

 private:
};
}  // namespace or2l::base_types