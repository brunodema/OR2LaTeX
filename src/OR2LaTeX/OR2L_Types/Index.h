#pragma once
#include "Exception.h"
#include "SymbolComponent.h"
#include <string>

namespace or2l {
class Index : public SymbolComponent {
 public:
  Index(const RegexString& name, const size_t lb, const size_t ub)
      : SymbolComponent(name, SymbolType::INDEX), lb_(lb), ub_(ub) {
    if (ub <= lb) {
      throw Exception(ExceptionType::ERR_INDEX_BOUNDS);
    }
  }
  ~Index() override = default;

  bool operator==(const Index& B) const {
    return this->lb_ == B.lb_ && this->ub_ == B.ub_ && this->name_ == B.name_;
  }

  [[nodiscard]] inline size_t GetUB() const { return ub_; }
  [[nodiscard]] inline size_t GetLB() const { return lb_; }
  [[nodiscard]] inline size_t GetSize() const { return ub_ - lb_; }

 private:
  size_t lb_ = 0;
  size_t ub_ = 0;
};
}  // namespace or2l

template <>
struct std::hash<or2l::Index> {
  std::size_t operator()(const or2l::Index& k) const {
    // changed it to be based on their names, which makes sense when thinking
    // about the LaTeX implementation
    return std::hash<std::string>()(k.GetName());
  };
};