#include "VARIABLE.h"

std::vector<std::size_t> OR2L::VARIABLE::GetIndexSizes() const
{
	std::vector<size_t> IndexSizes;
	IndexSizes.reserve(_index_map.size());
	int i = 0;
	for (auto& index : _index_map)
	{
		IndexSizes.push_back(index.second.GetSize());
	}
    return IndexSizes;
}
