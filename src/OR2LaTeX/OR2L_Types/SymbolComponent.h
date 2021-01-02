#pragma once
#include "RegexString.h"
#include "SymbolType.h"
#include <memory>

namespace or2l {
class SymbolComponent {
 public:
  SymbolComponent(const RegexString& str, const SymbolType& type)
      : name_(str), type_(type) {}
  virtual ~SymbolComponent() = default;

  // virtual std::unique_ptr<SymbolComponent> operator()();
  [[nodiscard]] virtual inline RegexString GetName() const { return name_; }
  virtual inline void SetName(const RegexString& str) { name_ = str; }
  [[nodiscard]] virtual inline SymbolType GetType() const { return type_; }

 protected:
  RegexString name_;
  SymbolType type_;
};
}  // namespace or2l
