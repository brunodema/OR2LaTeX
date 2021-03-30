#include "Variable.h"

namespace or2l
{
Variable::Variable(const base_types::RegexString &_name, const VariableType _var_type,
                   const std::initializer_list<Index> _indexes)
    : Symbol(_name, SymbolType::VARIABLE), variable_type_(_var_type)
{
    for (auto &&index : _indexes)
    {
        indexes.insert(std::pair<base_types::RegexString, Index>(index.GetName(), index));
    }
}

VariableType Variable::GetVariableType() const
{
    return variable_type_;
}
} // namespace or2l
