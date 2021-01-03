#pragma once
#include "Vecxd.h"
#include <memory>

namespace or2l {
template <class T>
class ObjectWrapper {
 public:
  ObjectWrapper() = default;
  virtual ~ObjectWrapper() = default;

  virtual void CreateObjects();
  virtual void DestroyObjects();
  virtual T GetObject();

 private:
  base_types::Vecxd<std::unique_ptr<T>> objects_;
};
}  // namespace or2l
