#pragma once
#include <string>
#include <vector>

namespace or2l
{
// numeric limits
static constexpr double EPSILON = 0.000001;
static constexpr bool IsNumericallyNull(double _val)
{
    return _val < EPSILON && _val > -EPSILON;
}

std::string GetCurrentCombinationString(const std::vector<std::size_t> &_index_values);

} // namespace or2l
