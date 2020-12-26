#include "VARIABLE.h"

std::vector<std::size_t> OR2L::VARIABLE::GetIndexSizes() const
{
	std::vector<size_t> IndexSizes;
	IndexSizes.reserve(_indexes.size());
	int i = 0;
	for (auto& index : _indexes)
	{
		IndexSizes.push_back(index.second.GetSize());
	}
    return IndexSizes;
}
