#include "Auxiliary.h"

std::string or2l::GetCurrentCombinationString(
    const std::vector<std::size_t> &index_values) // later will have to implement the formatting rules ('_'
                                                  // or '^')
{
    std::string ret;
    for (const auto &index : index_values)
    {
        ret += "_" + std::to_string(index);
    }
    return ret;
}