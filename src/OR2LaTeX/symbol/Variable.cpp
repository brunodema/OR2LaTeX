#include "Variable.h"

namespace or2l
{
Variable::Variable(const base_types::RegexString &name, const VariableType var_type,
                   const std::initializer_list<Index> indexes)
    : SymbolComponent(name, SymbolType::VARIABLE), variable_type_(var_type)
{
    for (auto &&index : indexes)
    {
        indexes_.insert(std::pair<base_types::RegexString, Index>(index.GetName(), index));
    }
}

std::size_t Variable::GetNumberOfIndexes()
{
    return indexes_.size();
}

Index Variable::GetIndex(const base_types::RegexString &key) const
{
    return indexes_.at(key);
}

std::vector<std::size_t> Variable::GetIndexSizes() const
{
    std::vector<size_t> index_sizes;
    index_sizes.reserve(indexes_.size());
    int i = 0;
    for (const auto &index : indexes_)
    {
        index_sizes.push_back(index.second.GetSize());
    }
    return index_sizes;
}

std::vector<Index> Variable::GetIndexes() const
{
    std::vector<Index> ret;
    for (auto &&index : indexes_)
    {
        ret.push_back(index.second);
    }
    return ret;
}

VariableType Variable::GetVariableType() const
{
    return variable_type_;
}
} // namespace or2l
