#pragma once
#include "Vecxd.h"
#include <memory>

namespace or2l {
template <class T>
class ObjectWrapper {
 public:
  ObjectWrapper() = default;
  virtual ~ObjectWrapper() = default;

  virtual void CreateObjects() = 0;
  virtual void DestroyObjects() = 0;
  virtual const T* GetObjects() = 0;

 protected:
  base_types::Vecxd<std::unique_ptr<T>> objects_;
};
}  // namespace or2l
