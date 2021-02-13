#pragma once
#include <iostream>
#include <utility>

namespace or2l::base_types {
template <class T = double>
class Coordinates {
 public:
  Coordinates() = default;
  Coordinates(std::string pId, const T px, const T py)
      : id_(std::move(pId)), x_(px), y_(py) {}

  bool operator==(const Coordinates<T>& B)
      const  // the comparisson will target the coordinates themselves, not ids
  {
    return this->x_ == B.x_ && this->y_ == B.y_;
  };

  inline T x() const { return x_; }
  inline T y() const { return y_; }
  inline T Id() const { return id_; }
  inline T& x() { return this->x_; }
  inline T& y() { return this->y; }
  inline T& Id() { return this->id; }

 private:
  std::string id_ = "";
  T x_ = {};
  T y_ = {};
};
}  // namespace or2l::base_types