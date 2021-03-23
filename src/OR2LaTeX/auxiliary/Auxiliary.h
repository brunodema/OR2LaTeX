#pragma once
#include <string>
#include <vector>

namespace or2l
{
// numeric limits
static constexpr double EPSILON = 0.000001;
static constexpr bool IsNumericallyNull(double val)
{
    return val < EPSILON && val > -EPSILON;
}

std::string GetCurrentCombinationString(const std::vector<std::size_t> &index_values);

} // namespace or2l
