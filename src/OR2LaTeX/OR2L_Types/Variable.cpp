#include "Variable.h"

or2l::Variable::Variable(const or2l::RegexString& name,
                         const or2l::VariableType var_type,
                         const std::initializer_list<or2l::Index> indexes)
    : SymbolComponent(name, or2l::SymbolType::VARIABLE),
      variable_type_(var_type) {
  for (auto&& index : indexes) {
    indexes_.insert(
        std::pair<or2l::RegexString, or2l::Index>(index.GetName(), index));
  }
}

std::size_t or2l::Variable::GetNumberOfIndexes() { return indexes_.size(); }

or2l::Index or2l::Variable::GetIndex(const or2l::RegexString& key) const {
  return indexes_.at(key);
}

std::vector<std::size_t> or2l::Variable::GetIndexSizes() const {
  std::vector<size_t> index_sizes;
  index_sizes.reserve(indexes_.size());
  int i = 0;
  for (const auto& index : indexes_) {
    index_sizes.push_back(index.second.GetSize());
  }
  return index_sizes;
}

std::vector<or2l::Index> or2l::Variable::GetIndexes() const {
  std::vector<or2l::Index> ret;
  for (auto&& index : indexes_) {
    ret.push_back(index.second);
  }
  return ret;
}
