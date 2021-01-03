#pragma once
#include "Index.h"
#include "SymbolComponent.h"
#include "VariableType.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace or2l {
class Variable : public SymbolComponent {
 public:
  friend struct std::hash<Variable>;

  Variable(const RegexString& name,
           VariableType var_type = VariableType::CONTINUOUS,
           const std::initializer_list<Index> indexes = {})
      : SymbolComponent(name, SymbolType::VARIABLE), variable_type_(var_type) {
    for (auto&& index : indexes) {
      indexes_.insert(std::pair<RegexString, Index>(index.GetName(), index));
    }
  }
  ~Variable() override = default;

  bool operator==(const Variable& B) const {
    return this->name_ == B.name_ && this->indexes_ == B.indexes_;
  }

  inline std::size_t GetNumberOfIndexes() { return indexes_.size(); }
  inline Index GetIndex(const RegexString& key) const {
    return indexes_.at(key);
  }
  std::vector<size_t> GetIndexSizes() const;
  std::vector<Index> GetIndexes() const {
    std::vector<Index> ret;
    for (auto&& index : indexes_) {
      ret.push_back(index.second);
    }
    return ret;
  }

 private:
  std::unordered_map<RegexString, Index> indexes_ = {};
  VariableType variable_type_ = VariableType::CONTINUOUS;
};
}  // namespace or2l

template <>
struct std::hash<or2l::Variable> {
  std::size_t operator()(const or2l::Variable& k) const {
    // changed it to be based on their names, which makes sense when thinking
    // about the LaTeX implementation
    return std::hash<std::string>()(k.GetName());
  };
};
