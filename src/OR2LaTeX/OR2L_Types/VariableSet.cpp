#include "VariableSet.h"

void or2l::VariableSet::PopulateSet()  // rework to 'actually' make V.O.
{
  std::vector<size_t> index_lengths = this->template_variable_.GetIndexSizes();
  int i = 0;
  for (auto&& length : index_lengths) {
    this->variable_objects_.at(i).resize(length);
    ++i;
  }
}
