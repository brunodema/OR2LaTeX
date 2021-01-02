#include "VARIABLE.h"

std::vector<std::size_t> or2l::VARIABLE::GetIndexSizes() const {
  std::vector<size_t> index_sizes;
  index_sizes.reserve(indexes_.size());
  int i = 0;
  for (const auto& index : indexes_) {
    index_sizes.push_back(index.second.GetSize());
  }
  return index_sizes;
}
