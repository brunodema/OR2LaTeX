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
  Variable() : SymbolComponent("", SymbolType::VARIABLE) {};
  explicit Variable(const RegexString& name,
                    VariableType var_type = VariableType::CONTINUOUS,
                    std::initializer_list<Index> indexes = {});
  ~Variable() override = default;

  inline bool operator==(const Variable& B) const {
    return this->name_ == B.name_ && this->indexes_ == B.indexes_;
  }

  std::size_t GetNumberOfIndexes();
  Index GetIndex(const RegexString& key) const;
  std::vector<size_t> GetIndexSizes() const;
  std::vector<Index> GetIndexes() const;
  VariableType GetVariableType() const;
  std::vector<std::vector<size_t>> GetAllIndexCombinations() const;

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
